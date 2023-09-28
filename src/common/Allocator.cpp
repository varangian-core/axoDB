//
// Created by Yormingandr on 9/26/2023.
//

#include "Allocator.h"
#include <algorithm>

namespace axodb {

DataPointer BasicAllocator::Allocate(IndexType size) {
    return new uint8_t[size];
}

void BasicAllocator::Deallocate(DataPointer pointer, IndexType size) {
    delete[] pointer;
}

DataPointer BasicAllocator::Reallocate(DataPointer pointer, IndexType old_size, IndexType new_size) {
    DataPointer new_pointer = new uint8_t[new_size];
    std::copy(pointer, pointer + std::min(old_size, new_size), new_pointer);
    delete[] pointer;
    return new_pointer;
}

} // namespace axodb