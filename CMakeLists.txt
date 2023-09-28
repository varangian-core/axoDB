cmake_minimum_required(VERSION 3.10)

project(axoDB)

set(CMAKE_CXX_STANDARD 17)

# Add the source files for your project
add_executable(axoDB
  src/main.cpp
  src/common/Allocator.cpp
  src/common/Buffer.cpp
)

# Add the include directories for your project
target_include_directories(axoDB PRIVATE
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/src/common
)

# Download and build the Google Test library
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

# Add the test executable
add_executable(axoDB_test
  tests/test_axoDB.cpp
  src/common/Allocator.cpp
  src/common/Buffer.cpp
)

# Add the include directories for the test executable
target_include_directories(axoDB_test PRIVATE
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/src/common
  ${googletest_SOURCE_DIR}/googletest/include
)

# Link the test executable with the Google Test library
target_link_libraries(axoDB_test PRIVATE gtest_main)

# Add a test
add_test(NAME axoDB_test COMMAND axoDB_test)