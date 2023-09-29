#include "BufferPoolManager.h"

Page::Page(page_id_t page_id, char *data)
    : page_id_(page_id), data_(data), is_dirty_(false), is_pinned_(false) {}

Page::~Page() {}

page_id_t Page::GetPageId() const {
    return page_id_;
}

char *Page::GetData() {
    return data_;
}

bool Page::IsDirty() const {
    return is_dirty_;
}

void Page::SetDirty(bool is_dirty) {
    is_dirty_ = is_dirty;
}

bool Page::Pin() {
    if (is_pinned_) {
        return false;
    }
    is_pinned_ = true;
    return true;
}

bool Page::Unpin(bool is_dirty) {
    if (!is_pinned_) {
        return false;
    }
    is_pinned_ = false;
    is_dirty_ = is_dirty || is_dirty_;
    return true;
}

DiskManager::DiskManager(const std::string &db_file, size_t num_pages)
    : db_file_(db_file, std::ios::in | std::ios::out | std::ios::binary),
      num_pages_(num_pages) {
    if (!db_file_.is_open()) {
        std::cerr << "Failed to open database file: " << db_file << std::endl;
        std::exit(EXIT_FAILURE);
    }
    db_file_.seekg(0, std::ios::end);
    size_t file_size = db_file_.tellg();
    if (file_size < num_pages_ * PAGE_SIZE) {
        db_file_.seekp(num_pages_ * PAGE_SIZE - 1, std::ios::beg);
        db_file_.put('\0');
    }
    db_file_.seekg(0, std::ios::beg);
    for (size_t i = 0; i < num_pages_; i++) {
        page_map_[i] = false;
    }
}

DiskManager::~DiskManager() {
    db_file_.close();
}

bool DiskManager::ReadPage(page_id_t page_id, char *page_data) {
    if (page_id >= num_pages_) {
        return false;
    }
    std::lock_guard<std::mutex> lock(latch_);
    db_file_.seekg(page_id * PAGE_SIZE, std::ios::beg);
    db_file_.read(page_data, PAGE_SIZE);
    return true;
}

bool DiskManager::WritePage(page_id_t page_id, const char *page_data) {
    if (page_id >= num_pages_) {
        return false;
    }
    std::lock_guard<std::mutex> lock(latch_);
    db_file_.seekp(page_id * PAGE_SIZE, std::ios::beg);
    db_file_.write(page_data, PAGE_SIZE);
    return true;
}

page_id_t DiskManager::AllocatePage() {
    std::lock_guard<std::mutex> lock(latch_);
    for (page_id_t i = 0; i < num_pages_; i++) {
        if (!page_map_[i]) {
            page_map_[i] = true;
            return i;
        }
    }
    return INVALID_PAGE_ID;
}

bool DiskManager::DeallocatePage(page_id_t page_id) {
    if (page_id >= num_pages_) {
        return false;
    }
    std::lock_guard<std::mutex> lock(latch_);
    page_map_[page_id] = false;
    return true;
}

size_t DiskManager::GetNumPages() const {
    return num_pages_;
}

BufferPoolManager::BufferPoolManager(size_t pool_size, DiskManager *disk_manager)
    : pool_size_(pool_size), disk_manager_(disk_manager) {}

BufferPoolManager::~BufferPoolManager() {}

Page *BufferPoolManager::NewPage() {
    std::lock_guard<std::mutex> lock(latch_);
    if (free_list_.empty()) {
        if (page_table_.size() >= pool_size_) {
            return nullptr;
        }
        page_id_t page_id = disk_manager_->AllocatePage();
        if (page_id == INVALID_PAGE_ID) {
            return nullptr;
        }
        char *data = new char[PAGE_SIZE];
        std::memset(data, 0, PAGE_SIZE);
        std::shared_ptr<Page> page = std::make_shared<Page>(page_id, data);
        page_table_[page_id] = page;
        return page.get();
    } else {
        std::shared_ptr<Page> page = free_list_.front();
        free_list_.pop_front();
        page_table_[page->GetPageId()] = page;
        return page.get();
    }
}

bool BufferPoolManager::DeletePage(page_id_t page_id) {
    std::lock_guard<std::mutex> lock(latch_);
    auto it = page_table_.find(page_id);
    if (it == page_table_.end()) {
        return false;
    }
    std::shared_ptr<Page> page = it->second;
    if (page->IsDirty()) {
        FlushPage(page_id);
    }
    disk_manager_->DeallocatePage(page_id);
    page_table_.erase(it);
    free_list_.push_back(page);
    return true;
}

Page *BufferPoolManager::FetchPage(page_id_t page_id) {
    std::lock_guard<std::mutex> lock(latch_);
    auto it = page_table_.find(page_id);
    if (it != page_table_.end()) {
        std::shared_ptr<Page> page = it->second;
        if (!page->Pin()) {
            return nullptr;
        }
        return page.get();
    }
    if (page_table_.size() >= pool_size_) {
        return nullptr;
    }
    char *data = new char[PAGE_SIZE];
    if (!disk_manager_->ReadPage(page_id, data)) {
        delete[] data;
        return nullptr;
    }
    std::shared_ptr<Page> page = std::make_shared<Page>(page_id, data);
    page_table_[page_id] = page;
    if (!page->Pin()) {
        page_table_.erase(page_id);
        return nullptr;
    }
    return page.get();
}

bool BufferPoolManager::UnpinPage(page_id_t page_id, bool is_dirty) {
    std::lock_guard<std::mutex> lock(latch_);
    auto it = page_table_.find(page_id);
    if (it == page_table_.end()) {
        return false;
    }
    std::shared_ptr<Page> page = it->second;
    if (!page->Unpin(is_dirty)) {
        return false;
    }
    if (!page->IsPinned()) {
        free_list_.push_back(page);
    }
    return true;
}

bool BufferPoolManager::FlushPage(page_id_t page_id) {
    std::lock_guard<std::mutex> lock(latch_);
    auto it = page_table_.find(page_id);
    if (it == page_table_.end()) {
        return false;
    }
    std::shared_ptr<Page> page = it->second;
    if (!page->IsDirty()) {
        return true;
    }
    if (!disk_manager_->WritePage(page_id, page->GetData())) {
        return false;
    }
    page->SetDirty(false);
    return true;
}

void BufferPoolManager::FlushAllPages() {
    std::lock_guard<std::mutex> lock(latch_);
    for (auto &entry : page_table_) {
        FlushPage(entry.first);
    }
}