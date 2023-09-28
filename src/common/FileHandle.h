//
// Created by Yormingandr on 9/27/2023.
//

#ifndef AXODB_FILEHANDLE_H
#define AXODB_FILEHANDLE_H

#include <cstdint>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#else
#include <fcntl.h>
#include <unistd.h>
#endif

namespace axodb {

    class FileHandle {
    public:
        FileHandle(const std::string& file_path);
        ~FileHandle();

        void Open();
        void Close();
        void Read(uint64_t location, uint64_t size, uint8_t* buffer);
        void Write(uint64_t location, uint64_t size, const uint8_t* buffer);

    private:
        std::string file_path_;

#ifdef _WIN32
        HANDLE file_handle_;
#else
        int file_descriptor_;
#endif
    };

} // namespace axodb

#endif // AXODB_FILEHANDLE_H