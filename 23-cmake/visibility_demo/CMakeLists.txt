cmake_minimum_required(VERSION 3.16)
project(visibility_demo)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib_private)
add_subdirectory(lib_public)
add_subdirectory(lib_interface)
add_subdirectory(app)
