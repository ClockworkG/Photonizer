cmake_minimum_required(VERSION 3.12...3.13)

project(Sample
        VERSION 1.0
        DESCRIPTION "Example projet for C++ CMake")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(tests)
