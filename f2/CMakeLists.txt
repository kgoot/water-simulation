cmake_minimum_required(VERSION 3.7)
project(f2)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(deps)
include_directories(deps/glad/include)
add_subdirectory(src)