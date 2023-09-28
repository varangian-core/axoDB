cmake_minimum_required(VERSION 3.27)

project(axoDB)

set(CMAKE_CXX_STANDARD 17)

# Add the source files for your project
add_executable(axoDB
  src/main.cpp
  src/common/Allocator.cpp
  src/common/Buffer.cpp
  src/common/FileHandle.cpp
)

# Add the include directories for your project
target_include_directories(axoDB PRIVATE
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/src/common
)

# Platform-specific dependencies and settings
if(UNIX)
    # Add Linux/MacOS specific build settings and dependencies
    # e.g., target_link_libraries(axoDB PRIVATE m)
elseif(WIN32)
    # Add Windows specific build settings and dependencies
    # No specific settings or dependencies for now
endif()
