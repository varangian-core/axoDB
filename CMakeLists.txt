cmake_minimum_required(VERSION 3.10)

project(axoDB VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable using source files in the src/ directory
add_executable(axoDB src/main.cpp src/axoDB.cpp
        src/common/Allocator.cpp
        src/common/Allocator.h)

# If you have unit tests in the tests/ directory, you can add them like this:
enable_testing()
add_executable(TestAxoDB tests/test_axoDB.cpp src/axoDB.cpp)
add_test(NAME TestAxoDB COMMAND TestAxoDB)
