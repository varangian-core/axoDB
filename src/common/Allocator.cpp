//
// Created by Yormingandr on 9/26/2023.
//

#include <cstddef>
#include <cstdint>
#include <algorithm>

namespace axodb {

    using DataPointer = uint8_t *;
    using IndexType = size_t;

    class Allocator {
    public:
        virtual ~Allocator() = default;

        virtual DataPointer Allocate(IndexType size) = 0;
        virtual void Deallocate(DataPointer p, IndexType size) = 0;
        virtual DataPointer ReallocateData(DataPointer pointer, IndexType old_size, IndexType new_size) = 0;
    };


    class BasicAllocator: public Allocator {
    public:
        DataPointer Allocate(IndexType size) override {
            return new uint8_t[size];
        }


        void Deallocate(DataPointer pointer, IndexType size) override {
            delete[] pointer;
        }

        DataPointer ReallocateData(DataPointer pointer, IndexType  old_size, IndexType  new_size) override {
            DataPointer  new_pointer = new uint8_t[new_size];
            std::copy(pointer, pointer + std::min(old_size, new_size), new_pointer);
            delete[] pointer;
            return new_pointer;
            }
    };

}