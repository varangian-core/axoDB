cmake_minimum_required(VERSION 3.26)

project(axoDB)

set(CMAKE_CXX_STANDARD 17)

# Add all .cpp files in the src directory to the source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add the source files for your project
add_executable(axoDB ${SOURCES}
        src/common/Btree.cpp
        src/common/Btree.h
        src/common/BufferFrame.cpp
        src/common/BufferFrame.h
        src/common/Node.cpp
        src/common/Node.h
        src/concurrency/TransactionManager.cpp
        src/concurrency/TransactionManager.h
        src/concurrency/LogManager.cpp
        src/concurrency/LogManager.h)

# Add the include directories for your project
target_include_directories(axoDB PRIVATE
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/common
        ${PROJECT_SOURCE_DIR}/src/buffer
        ${PROJECT_SOURCE_DIR}/src/concurrency
)

# Platform-specific dependencies and settings
if (UNIX)
    # Add Linux/MacOS specific build settings and dependencies
    # e.g., target_link_libraries(axoDB PRIVATE m)
elseif (WIN32)
    # Add Windows specific build settings and dependencies
    # No specific settings or dependencies for now
endif ()