//
// Created by Yormingandr on 9/26/2023.
//
//
// Created by Yormingandr on 9/26/2023.
//

#include "Buffer.h"
#include "FileHandle.h"
#include <cstring>

namespace axodb {

    Buffer::Buffer(Allocator& allocator, FileBufferType type, uint64_t user_size)
        : m_allocator(&allocator), m_type(type), m_user_size(user_size), m_buffer(nullptr), m_size(0) {
        Resize(user_size);
    }

    Buffer::Buffer(Buffer& source, FileBufferType type)
        : m_allocator(source.m_allocator), m_type(type), m_user_size(source.m_user_size), m_buffer(nullptr), m_size(0) {
        Resize(source.m_size);
        std::memcpy(m_buffer, source.m_buffer, source.m_size);
    }

    Buffer::~Buffer() {
        Clear();
    }

    void Buffer::Resize(uint64_t new_size) {
        if (new_size > m_user_size) {
            throw std::invalid_argument("Buffer size exceeds user size");
        }

        if (new_size > m_size) {
            void* new_buffer = m_allocator->Allocate(new_size);
            std::memcpy(new_buffer, m_buffer, m_size);
            m_allocator->Deallocate(m_buffer);
            m_buffer = new_buffer;
        }

        m_size = new_size;
    }

    void Buffer::Read(FileHandle& handle, uint64_t location) {
        handle.Seek(location);
        handle.Read(m_buffer, m_size);
    }

    void Buffer::Write(FileHandle& handle, uint64_t location) {
        handle.Seek(location);
        handle.Write(m_buffer, m_size);
    }

    void Buffer::Clear() {
        if (m_buffer) {
            m_allocator->Deallocate(m_buffer);
            m_buffer = nullptr;
            m_size = 0;
        }
    }

    void Buffer::Initialize(DebugInitialize initialize) {
        if (initialize == DebugInitialize::Zero) {
            std::memset(m_buffer, 0, m_size);
        }
    }

} // namespace axodb