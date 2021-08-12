cmake_minimum_required(VERSION 3.20)
project(lava-fbx LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(ext)
add_subdirectory(liblava-extras)
# add_subdirectory(demo)
