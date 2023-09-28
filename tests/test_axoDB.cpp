// test_axoDB.cpp

#include "../src/common/Allocator.h"
#include <gtest/gtest.h>

// Define a fixture for the tests
class AllocatorTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a new allocator for each test
        allocator = new axodb::BasicAllocator();
    }

    void TearDown() override {
        // Delete the allocator after each test
        delete allocator;
    }

    axodb::Allocator* allocator;
};

// Test the Allocate and Deallocate methods
TEST_F(AllocatorTest, AllocateAndDeallocate) {
    // Arrange
    axodb::IndexType size = 10;
    axodb::DataPointer ptr = allocator->Allocate(size);

    // Act
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

    // Assert
    // Check that the pointer is null after deallocation
    ASSERT_EQ(ptr, nullptr);
}