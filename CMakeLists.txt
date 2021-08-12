cmake_minimum_required(VERSION 3.20)
project(lava-fbx LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(liblava-extras)
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/../../liblava/ ${CMAKE_CURRENT_BINARY_DIR}/liblava)
# add_subdirectory(demo)
