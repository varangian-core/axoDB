//
// Created by Yormingandr on 9/27/2023.
//
#ifndef AXODB_BUFFER_H
#define AXODB_BUFFER_H

#include "Allocator.h"
#include "FileHandle.h" // Include this if FileHandle is used
#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <cstring>

namespace axodb {

    enum class FileBufferType {
        DEFAULT,
        LARGE,
        TINY
    };

    class Buffer {
    public:
        struct MemoryRequirement {
            size_t header_size;
            size_t alloc_size;
        };

        enum class DebugInitialize {
            NO_INITIALIZE,
            DEBUG_ZERO_INITIALIZE
        };

        Buffer(Allocator& allocator, FileBufferType type, uint64_t user_size);
        Buffer(Buffer& source, FileBufferType type);
        ~Buffer();

        void Resize(uint64_t new_size);
        void Read(FileHandle& handle, uint64_t location); // Uncommented
        void Write(FileHandle& handle, uint64_t location); // Uncommented
        void Clear();
        void Initialize(DebugInitialize initialize);

    private:
        Allocator& allocator_;
        FileBufferType type_;
        uint64_t user_size_;
        void* buffer_;
        uint64_t size_;
    };

} // namespace axodb

#endif // AXODB_BUFFER_H