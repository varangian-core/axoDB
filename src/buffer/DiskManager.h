#ifndef DISK_MANAGER_H
#define DISK_MANAGER_H

#include <string>
#include <fstream>

// Define the page_id_t type
using page_id_t = uint64_t;

class DiskManager {
public:
    static const size_t PAGE_SIZE = 4096; // Page size in bytes

    DiskManager(const std::string& file_path);
    ~DiskManager();

    bool ReadPage(page_id_t page_id, char* buffer);
    bool WritePage(page_id_t page_id, const char* buffer);
    page_id_t AllocatePage();
    bool DeallocatePage(page_id_t page_id);

private:
    std::string file_path_;
    std::fstream file_stream_;
};

#endif // DISK_MANAGER_H
