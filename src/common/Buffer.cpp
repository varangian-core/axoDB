//
// Created by Yormingandr on 9/27/2023.
//


#include "Buffer.h"
#include "Allocator.h"


namespace axodb {

    Buffer::Buffer(Allocator &allocator, FileBufferType type, uint64_t user_size)
            : allocator(allocator), type(type) {
        Init();
        if (user_size) {
            Resize(user_size);
        }
    }

    Buffer::Buffer(Allocator &allocator, FileBufferType type_p)
            : allocator(source.allocator), type(type_p) {
        buffer = source.buffer;
        size = source.size;
        internal_buffer = source.internal_buffer;
        internal_size = source.internal_size;

        source.Init();
    }

    Buffer::~Buffer() {
        if (!internal_buffer) {
            return;
        }

        allocator.FreeData(
    }


    void Buffer::Init() {
        buffer = nullptr;
        size = 0;
        internal_buffer = nullptr;
        internal_size = 0;
    }


    void Buffer::ReallocBuffer(size_t new_size) {
        uint8_t *new_buffer;
        if (internal_buffer) {
            new_buffer = reinterpret_cast<uint8_t *>(allocator.ReallocateData(internal_buffer, internal_size, new_size))
        } else {
            new_buffer = allocator.AllocateData(new_size);
        }

        if (!new_buffer) {
            throw std::bad_alloc();
        }

        internal_buffer = new_buffer;
        internal_size = new_size;
        buffer = nullptr;
        size = 0;
    }


    Buffer::MemoryRequirement Buffer::CalculateMemory(uint64_t user_size) {
        MemoryRequirement result;
        result.header_size = 16; //Basic arbitrary value
        result.alloc_size = user_size + result.header_size //Need something better here
        return result;
    }


    void Buffer::Resize(uint64_t new_size) {
        auto req = CalculateMemroy(new_size);
        ReallocBuffer(req.alloc_size);
        if (new_size > 0) {
            buffer = internal_buffer + req.header_size;
            size = internal_size - req.header_size;
        }
    }


    void Buffer::Read(/*FileHandle &handle,*/ uint64_t location) {
        //TODO: implement read
    }

    void Buffer::Write(/*FileHandle &handle,*/ uint64_t location) {
        //TODO: implement write
    }

    void Buffer::Clear() {
        std::memset(internal_buffer, 0, internal_size);
    }

    void Buffer::Initialize(DebugInitialize initialize) {
        uint8_t value = initialize == DebugInitialize::DEBUG_ZERO_INITIALIZE ? 0 : 0xFF;
        std::memset(internal_buffer, value, internal_size);
    }

}