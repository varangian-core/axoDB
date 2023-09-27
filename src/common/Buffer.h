//
// Created by Yormingandr on 9/27/2023.
//

#ifndef AXODB_BUFFER_H
#define AXODB_BUFFER_H

#include "Allocator.h"
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


        Buffer(Allocator &allocator, FileBufferType type, uint64_t user_size);
        Buffer(Buffer &source, FileBufferType type);
        ~Buffer();

        void Resize(uint64_t new_size);
        void Read(/*FileHandle &handle,*/ uint64_t location);
        void Write(/*FileHandle &handle,*/ uint64_t location);
        void Clear();
        void Initialize(DebugInitialize initialize);

    private:
        void Init();
        void ReallocBuffer(size_t new_size);
        static MemoryRequirement CalculateMemory(uint64_t user_size);

        Allocator &allocator;
        FileBufferType type;
        uint8_t *buffer;
        size_t size;
        uint8_t *internal_buffer;
        size_t internal_size;
    };

}
#endif //AXODB_BUFFER_H
