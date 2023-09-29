#include "DiskManager.h"
#include <iostream>

DiskManager::DiskManager(const std::string& file_path)
    : file_path_(file_path) {
    // Open the file for binary I/O operations
    file_stream_.open(file_path_, std::ios::in | std::ios::out | std::ios::binary);
    if (!file_stream_.is_open()) {
        // File doesn't exist, create a new one
        file_stream_.open(file_path_, std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
        if (!file_stream_.is_open()) {
            std::cerr << "Failed to create or open the file: " << file_path << std::endl;
            // Handle the error (e.g., throw an exception)
        }
    }
}

DiskManager::~DiskManager() {
    if (file_stream_.is_open()) {
        file_stream_.close();
    }
}

bool DiskManager::ReadPage(page_id_t page_id, char* buffer) {
    if (!file_stream_.is_open()) {
        std::cerr << "File is not open for reading." << std::endl;
        return false;
    }

    // Calculate the offset based on the page_id and PAGE_SIZE
    std::streamoff offset = static_cast<std::streamoff>(page_id) * static_cast<std::streamoff>(PAGE_SIZE);

    // Seek to the appropriate position in the file
    file_stream_.seekg(offset);

    // Read the page into the buffer
    file_stream_.read(buffer, PAGE_SIZE);

    // Check if any errors occurred during reading
    if (!file_stream_.good()) {
        std::cerr << "Error reading page from disk." << std::endl;
        return false;
    }

    return true;
}

bool DiskManager::WritePage(page_id_t page_id, const char* buffer) {
    if (!file_stream_.is_open()) {
        std::cerr << "File is not open for writing." << std::endl;
        return false;
    }

    // Calculate the offset based on the page_id and PAGE_SIZE
    std::streamoff offset = static_cast<std::streamoff>(page_id) * static_cast<std::streamoff>(PAGE_SIZE);

    // Seek to the appropriate position in the file
    file_stream_.seekp(offset);

    // Write the page from the buffer to the file
    file_stream_.write(buffer, PAGE_SIZE);

    // Check if any errors occurred during writing
    if (!file_stream_.good()) {
        std::cerr << "Error writing page to disk." << std::endl;
        return false;
    }

    return true;
}

page_id_t DiskManager::AllocatePage() {
    if (!file_stream_.is_open()) {
        std::cerr << "File is not open for allocation." << std::endl;
        return 0; // Return 0 to indicate failure
    }

    // Calculate the total number of pages in the file
    file_stream_.seekg(0, std::ios::end);
    size_t total_pages = static_cast<size_t>(file_stream_.tellg() / PAGE_SIZE);

    // Seek back to the end of the file
    file_stream_.seekp(0, std::ios::end);

    // Allocate a new page at the end of the file
    char empty_page[PAGE_SIZE] = {0}; // Initialize a page with zeros
    file_stream_.write(empty_page, PAGE_SIZE);

    // Check if any errors occurred during allocation
    if (!file_stream_.good()) {
        std::cerr << "Error allocating page on disk." << std::endl;
        return 0; // Return 0 to indicate failure
    }

    return total_pages; // Return the page_id of the newly allocated page
}

bool DiskManager::DeallocatePage(page_id_t page_id) {
    if (!file_stream_.is_open()) {
        std::cerr << "File is not open for deallocation." << std::endl;
        return false;
    }

    // Calculate the offset based on the page_id and PAGE_SIZE
    std::streamoff offset = static_cast<std::streamoff>(page_id) * static_cast<std::streamoff>(PAGE_SIZE);

    // Seek to the appropriate position in the file
    file_stream_.seekp(offset);

    // Write an empty page (zero-filled) to deallocate the page
    char empty_page[PAGE_SIZE] = {0};
    file_stream_.write(empty_page, PAGE_SIZE);

    // Check if any errors occurred during deallocation
    if (!file_stream_.good()) {
        std::cerr << "Error deallocating page on disk." << std::endl;
        return false;
    }

    return true;
}
