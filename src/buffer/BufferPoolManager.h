#pragma once

#include <unordered_map>
#include <list>
#include <mutex>
#include <memory>

typedef uint64_t page_id_t;

class Page {
public:
    Page(page_id_t page_id, char *data);

    ~Page();

    page_id_t GetPageId() const;

    char *GetData();

    bool IsDirty() const;

    void SetDirty(bool is_dirty);

    bool Pin();

    bool Unpin(bool is_dirty);

private:
    page_id_t page_id_;
    char *data_;
    bool is_dirty_;
    bool is_pinned_;
};

class DiskManager {
public:
    DiskManager(const std::string &db_file, size_t num_pages);

    ~DiskManager();

    bool ReadPage(page_id_t page_id, char *page_data);

    bool WritePage(page_id_t page_id, const char *page_data);

    page_id_t AllocatePage();

    bool DeallocatePage(page_id_t page_id);

    size_t GetNumPages() const;

private:
    std::fstream db_file_;
    size_t num_pages_;
    std::unordered_map<page_id_t, bool> page_map_;
    std::mutex latch_;
};

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
    std::list<std::shared_ptr<Page>> free_list_;
    std::mutex latch_;
};