//
// Created by Yormingandr on 9/27/2023.
//
#include "Buffer.h"
#include "FileHandle.h"
#include <cstring>

namespace axodb {

    Buffer::Buffer(Allocator& allocator, FileBufferType type, uint64_t user_size)
        : allocator_(allocator), type_(type), user_size_(user_size), buffer(nullptr), size_(0) {
        Resize(user_size_);
    }

    Buffer::Buffer(Buffer& source, FileBufferType type)
        : allocator_(source.allocator_), type_(type), user_size_(source.user_size_), buffer(nullptr), size_(0) {
        Resize(source.size_);
        std::memcpy(buffer, source.buffer, source.size_);
    }

    Buffer::~Buffer() {
        Clear();
    }

    void Buffer::Resize(uint64_t new_size) {
        if (new_size > user_size) {
            throw std::invalid_argument("Buffer size exceeds user size");
        }

        if (new_size > size) {
            void* new_buffer = allocator->Allocate(new_size);
            std::memcpy(new_buffer, buffer, size);
            allocator->Deallocate(buffer);
            buffer = new_buffer;
        }

        size = new_size;
    }

    void Buffer::Read(FileHandle& handle, uint64_t location) {
        handle.Seek(location);
        handle.Read(buffer, size);
    }

    void Buffer::Write(FileHandle& handle, uint64_t location) {
        handle.Seek(location);
        handle.Write(buffer, size);
    }

    void Buffer::Clear() {
        if (buffer) {
            allocator->Deallocate(buffer);
            buffer = nullptr;
            size = 0;
        }
    }

    void Buffer::Initialize(DebugInitialize initialize) {
        if (initialize == DebugInitialize::Zero) {
            std::memset(buffer, 0, size);
        }
    }

} // namespace axodb