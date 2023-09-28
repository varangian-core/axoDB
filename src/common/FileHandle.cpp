//
// Created by Yormingandr on 9/27/2023.
//

#include "FileHandle.h"
#include <stdexcept>

namespace axodb {

    FileHandle::FileHandle(const std::string& file_path) : file_path_(file_path)
#ifdef _WIN32
    , file_handle_(INVALID_HANDLE_VALUE)
#else
    , file_descriptor_(-1)
#endif
    {}

    FileHandle::~FileHandle() {
        Close();
    }

    void FileHandle::Open() {
#ifdef _WIN32
        if (file_handle_ != INVALID_HANDLE_VALUE) {
            throw std::runtime_error("File is already open.");
        }

        file_handle_ = CreateFileA(file_path_.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

        if (file_handle_ == INVALID_HANDLE_VALUE) {
            throw std::runtime_error("Failed to open file.");
        }
#else
        if (file_descriptor_ != -1) {
            throw std::runtime_error("File is already open.");
        }

        file_descriptor_ = open(file_path_.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

        if (file_descriptor_ == -1) {
            throw std::runtime_error("Failed to open file.");
        }
#endif
    }

    void FileHandle::Close() {
#ifdef _WIN32
        if (file_handle_ != INVALID_HANDLE_VALUE) {
            CloseHandle(file_handle_);
            file_handle_ = INVALID_HANDLE_VALUE;
        }
#else
        if (file_descriptor_ != -1) {
            close(file_descriptor_);
            file_descriptor_ = -1;
        }
#endif
    }

    void FileHandle::Read(uint64_t location, uint64_t size, uint8_t* buffer) {
#ifdef _WIN32
        if (file_handle_ == INVALID_HANDLE_VALUE) {
            throw std::runtime_error("File is not open.");
        }

        LARGE_INTEGER li;
        li.QuadPart = location;
        if (!SetFilePointerEx(file_handle_, li, NULL, FILE_BEGIN)) {
            throw std::runtime_error("Failed to seek to location.");
        }

        DWORD bytes_read;
        if (!ReadFile(file_handle_, buffer, size, &bytes_read, NULL)) {
            throw std::runtime_error("Failed to read from file.");
        }
#else
        if (file_descriptor_ == -1) {
            throw std::runtime_error("File is not open.");
        }

        if (lseek(file_descriptor_, location, SEEK_SET) == -1) {
            throw std::runtime_error("Failed to seek to location.");
        }

        if (read(file_descriptor_, buffer, size) == -1) {
            throw std::runtime_error("Failed to read from file.");
        }
#endif
    }

    void FileHandle::Write(uint64_t location, uint64_t size, const uint8_t* buffer) {
#ifdef _WIN32
        if (file_handle_ == INVALID_HANDLE_VALUE) {
            throw std::runtime_error("File is not open.");
        }

        LARGE_INTEGER li;
        li.QuadPart = location;
        if (!SetFilePointerEx(file_handle_, li, NULL, FILE_BEGIN)) {
            throw std::runtime_error("Failed to seek to location.");
        }

        DWORD bytes_written;
        if (!WriteFile(file_handle_, buffer, size, &bytes_written, NULL)) {
            throw std::runtime_error("Failed to write to file.");
        }
#else
        if (file_descriptor_ == -1) {
            throw std::runtime_error("File is not open.");
        }

        if (lseek(file_descriptor_, location, SEEK_SET) == -1) {
            throw std::runtime_error("Failed to seek to location.");
        }

        if (write(file_descriptor_, buffer, size) == -1) {
            throw std::runtime_error("Failed to write to file.");
        }
#endif
    }

} // namespace axodb