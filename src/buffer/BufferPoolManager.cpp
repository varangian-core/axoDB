#include "BufferPoolManager.h"

BufferPoolManager::BufferPoolManager(size_t pool_size, DiskManager *disk_manager)
    : pool_size_(pool_size), disk_manager_(disk_manager) {}

BufferPoolManager::~BufferPoolManager() {
    // Ensure all pages are flushed before destruction.
    FlushAllPages();
}

Page *BufferPoolManager::NewPage() {
    // TODO: Implement page replacement policy
    if (page_table_.size() >= pool_size_) {
        return nullptr;
    }
    page_id_t page_id = disk_manager_->AllocatePage();
    std::unique_ptr<char[]> data(new char[DiskManager::PAGE_SIZE]);
    Page *page = new Page(page_id, std::move(data));
    page_table_[page_id] = std::shared_ptr<Page>(page);
    return page;
}

bool BufferPoolManager::DeletePage(page_id_t page_id) {
    auto it = page_table_.find(page_id);
    if (it == page_table_.end()) {
        return false;
    }
    disk_manager_->DeallocatePage(page_id);
    page_table_.erase(it);
    return true;
}

Page *BufferPoolManager::FetchPage(page_id_t page_id) {
    std::unique_lock<std::mutex> latch(latch_);
    auto it = page_table_.find(page_id);
    if (it != page_table_.end()) {
        return it->second.get();
    }
    std::unique_ptr<char[]> data(new char[DiskManager::PAGE_SIZE]);
    if (!disk_manager_->ReadPage(page_id, data.get())) {
        return nullptr;
    }
    Page *page = new Page(page_id, std::move(data));
    page_table_[page_id] = std::shared_ptr<Page>(page);
    return page;
}

bool BufferPoolManager::UnpinPage(page_id_t page_id, bool is_dirty) {
    std::unique_lock<std::mutex> latch(latch_);
    auto it = page_table_.find(page_id);
    if (it == page_table_.end()) {
        return false;
    }
    return it->second->Unpin(is_dirty);
}

bool BufferPoolManager::FlushPage(page_id_t page_id) {
    std::unique_lock<std::mutex> latch(latch_);
    auto it = page_table_.find(page_id);
    if (it == page_table_.end()) {
        return false;
    }
    Page *page = it->second.get();
    if (page->IsDirty()) {
        disk_manager_->WritePage(page_id, page->GetData());
        page->SetDirty(false);
    }
    return true;
}

void BufferPoolManager::FlushAllPages() {
    std::unique_lock<std::mutex> latch(latch_);
    for (auto &entry : page_table_) {
        Page *page = entry.second.get();
        if (page->IsDirty()) {
            disk_manager_->WritePage(page->GetPageId(), page->GetData());
            page->SetDirty(false);
        }
    }
}
