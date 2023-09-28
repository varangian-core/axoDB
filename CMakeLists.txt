# CMakeLists.txt for axodb project

# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(axodb VERSION 1.0)

# Set the C++ standard and required features
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add subdirectories for each component of the project
# The 'src' directory contains the source code for the main executable
# The 'tests' directory contains the source code for the unit tests
add_subdirectory(src)
add_subdirectory(tests)

# Use FetchContent to download and build gtest
# This will download and build the Google Test framework as part of the CMake build process
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)