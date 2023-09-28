//
// Created by Yormingandr on 9/26/2023.
//
#include "../src/common/Allocator.h"
#include <gtest/gtest.h>

// Define a fixture for the tests
class AllocatorTest : public ::testing::Test {
protected:
    // Create a new allocator for each test
    void SetUp() override {
        allocator = new axodb::BasicAllocator();
    }

    // Delete the allocator after each test
    void TearDown() override {
        delete allocator;
    }

    axodb::Allocator* allocator;
};

// Test the Allocate and Deallocate methods
TEST_F(AllocatorTest, AllocateAndDeallocate) {
    axodb::IndexType size = 10;
    axodb::DataPointer ptr = allocator->Allocate(size);

    // Check that the pointer is not null
    ASSERT_NE(ptr, nullptr);

    // Check that the allocated memory is writable
    for (axodb::IndexType i = 0; i < size; ++i) {
        ptr[i] = static_cast<uint8_t>(i);
    }

    // Check that the allocated memory is readable
    for (axodb::IndexType i = 0; i < size; ++i) {
        ASSERT_EQ(ptr[i], static_cast<uint8_t>(i));
    }

    allocator->Deallocate(ptr, size);

    // Check that the pointer is null after deallocation
    ASSERT_EQ(ptr, nullptr);
}

// Test the Allocate method with a size of zero
TEST_F(AllocatorTest, AllocateZeroSize) {
    axodb::IndexType size = 0;
    axodb::DataPointer ptr = allocator->Allocate(size);

    // Check that the pointer is null
    ASSERT_EQ(ptr, nullptr);
}

// Test the Allocate method with a negative size
TEST_F(AllocatorTest, AllocateNegativeSize) {
    axodb::IndexType size = -1;
    axodb::DataPointer ptr = allocator->Allocate(size);

    // Check that the pointer is null
    ASSERT_EQ(ptr, nullptr);
}

// Test the Deallocate method with a null pointer
TEST_F(AllocatorTest, DeallocateNullPointer) {
    axodb::IndexType size = 10;
    axodb::DataPointer ptr = nullptr;

    allocator->Deallocate(ptr, size);

    // Check that the Deallocate method does not crash with a null pointer
    SUCCEED();
}

// Test the Deallocate method with a negative size
TEST_F(AllocatorTest, DeallocateNegativeSize) {
    axodb::IndexType size = -1;
    axodb::DataPointer ptr = reinterpret_cast<axodb::DataPointer>(1);

    allocator->Deallocate(ptr, size);

    // Check that the Deallocate method does not crash with a negative size
    SUCCEED();
}