//
// Created by Yormingandr on 9/27/2023.
//

#include "Buffer.h"
//#include "FileHandle.h" // Uncomment this line if FileHandle is needed

namespace axodb {

    Buffer::Buffer(Allocator& allocator, FileBufferType type, uint64_t user_size) {
        // Implementation
    }

    Buffer::Buffer(Buffer& source, FileBufferType type) {
        // Implementation
    }

    Buffer::~Buffer() {
        // Implementation
    }

    void Buffer::Resize(uint64_t new_size) {
        // Implementation
    }

    void Buffer::Read(/*FileHandle& handle,*/ uint64_t location) {
        // Implementation
    }

    void Buffer::Write(/*FileHandle& handle,*/ uint64_t location) {
        // Implementation
    }

    void Buffer::Clear() {
        // Implementation
    }

    void Buffer::Initialize(DebugInitialize initialize) {
        // Implementation
    }

} // namespace axodb