//
// Created by Yormingandr on 9/26/2023.
//

#include <cstdef>
#include <cstint>

namespace axodb {

    using DataPointer = uint8_t *;
    using IndexType = size_t;

    class Allocator {
    public:
        virtual ~Allocator() = default;

        virtual DataPointer Allocate(IndexType size) = 0;

        virtual void Deallocate(Datapointer p, IndexType size) = 0;
    };


    class BasicAllocator: public Allocator {
    public:
        DataPointer Allocate(IndexType size) override {
            return new uint8_t[size];
        }


        void Deallocate(Datapointer p, IndexType size) override {
            delete[] p;
        }
    };

}