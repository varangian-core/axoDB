cmake_minimum_required(VERSION 3.10)

project(axodb)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable using source files in the src/ directory
add_executable(axoDB src/main.cpp src/axoDB.cpp
        src/common/Allocator.cpp
        src/common/Allocator.h
        src/common/Buffer.cpp
        src/common/Buffer.h)

# If you have unit tests in the tests/ directory, you can add them like this:
enable_testing()
add_executable(main src/main.cpp src/common/Allocator.h)
add_executable(allocator_test tests/test_axoDB.cpp src/common/allocator.h)
