//
// Created by Yormingandr on 9/27/2023.

#include "Buffer.h"
#include <cstring> // For std::memcpy
#include <stdexcept> // For std::invalid_argument

namespace axodb {

    Buffer::Buffer(Allocator& allocator, FileBufferType type, uint64_t user_size)
        : allocator_(allocator), type_(type), user_size_(user_size), buffer_(nullptr), size_(0) {
        Resize(user_size_);
    }

    Buffer::Buffer(Buffer& source, FileBufferType type)
        : allocator_(source.allocator_), type_(type), user_size_(source.user_size_), buffer_(nullptr), size_(0) {
        Resize(source.size_);
        std::memcpy(buffer_, source.buffer_, source.size_);
    }

    Buffer::~Buffer() {
        if (buffer_) {
            allocator_.Deallocate(static_cast<DataPointer>(buffer_), size_);
        }
    }

    void Buffer::Resize(uint64_t new_size) {
        if (new_size > user_size_) {
            throw std::invalid_argument("Buffer size exceeds user size");
        }

        if (new_size > size_) {
            DataPointer new_buffer = allocator_.Allocate(new_size);
            if (buffer_) {
                std::memcpy(new_buffer, static_cast<DataPointer>(buffer_), size_);
                allocator_.Deallocate(static_cast<DataPointer>(buffer_), size_);
            }
            buffer_ = static_cast<void*>(new_buffer);
        }

        size_ = new_size;
    }

    void Buffer::Read(FileHandle& handle, uint64_t location) {
    handle.Read(location, size_, static_cast<uint8_t*>(buffer_)); 
 }
} // namespace axodb