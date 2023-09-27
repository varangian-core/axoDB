//
// Created by Yormingandr on 9/26/2023.
//

#include "../src/common/Allocator.h"
#include <cassert>
//Should add gtest here

int main() {
    axodb::Allocator* allocator = new axodb:BasicAllocator();

    axodb::IndexType size = 10; //change the size accordingly
    axodb::DataPointer ptr = allocator->Allocate(size);

    for (axodb::IndexType i =0 ; i < size; ++i) {
        ptr[i] = static_cast<uint8_t>(i);
    }

    for (axodb::IndexType i =0 ; i < size; ++i) {
        assert(ptr[i] = i);
    }

    allocator->Deallocate(ptr,size);
    delete allocator;

    return 0;
}

