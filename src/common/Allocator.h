//
// Created by Yormingandr on 9/27/2023.
//

#ifndef AXODB_ALLOCATOR_H
#define AXODB_ALLOCATOR_H

#include <algorithm>
#include <cstddef>
#include <cstdint>

namespace axodb {

using DataPointer = uint8_t*;
using IndexType = size_t;

class Allocator {
public:
    virtual ~Allocator() = default;
    virtual DataPointer Allocate(IndexType size) = 0;
    virtual void Deallocate(DataPointer p, IndexType size) = 0;
    virtual DataPointer Reallocate(DataPointer p, IndexType old_size, IndexType new_size) = 0;
};

class BasicAllocator : public Allocator {
public:
    DataPointer Allocate(IndexType size) override {
        return new uint8_t[size];
    }

    void Deallocate(DataPointer p, IndexType size) override {
        delete[] p;
    }

    DataPointer Reallocate(DataPointer p, IndexType old_size, IndexType new_size) override {
        DataPointer new_p = new uint8_t[new_size];
        std::copy(p, p + std::min(old_size, new_size), new_p);
        delete[] p;
        return new_p;
    }
};

} // namespace axodb
#endif