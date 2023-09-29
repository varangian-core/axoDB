#ifndef BUFFER_POOL_MANAGER_H
#define BUFFER_POOL_MANAGER_H

#include "Page.h"
#include "DiskManager.h"
#include <unordered_map>
#include <mutex>
#include <memory>

class BufferPoolManager {
public:
    BufferPoolManager(size_t pool_size, DiskManager *disk_manager);
    ~BufferPoolManager();

    Page *NewPage();
    bool DeletePage(page_id_t page_id);
    Page *FetchPage(page_id_t page_id);
    bool UnpinPage(page_id_t page_id, bool is_dirty);
    bool FlushPage(page_id_t page_id);
    void FlushAllPages();

private:
    size_t pool_size_;
    DiskManager *disk_manager_;
    std::unordered_map<page_id_t, std::shared_ptr<Page>> page_table_;
    std::mutex latch_;
};

#endif // BUFFER_POOL_MANAGER_H
