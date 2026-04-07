cmake_minimum_required(VERSION 4.2)

# Set experimental flag to enable `import std` support from CMake.
# This must be enabled before C++ language support.
#set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD
        # This specific value changes as experimental support evolves. See
        # `Help/dev/experimental.rst` in the CMake source corresponding to
        # your CMake build for the exact value to use.
#        "d0edc3af-4c50-42ea-a356-e2862fe7a444")

project(openLudo LANGUAGES CXX)

#set(CMAKE_CXX_MODULE_STD 1)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(model)
add_subdirectory(controller)