cmake_minimum_required(VERSION 3.20)
project(liblava-extras LANGUAGES CXX)

set(LIBLAVA_EXTRAS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/liblava-extras)

message(">> lava-extras::core")
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/empty.cpp "")

add_library(lava-extras.core STATIC
        ${CMAKE_CURRENT_BINARY_DIR}/empty.cpp
        ${LIBLAVA_EXTRAS_DIR}/lava-extras.hpp
        ${LIBLAVA_EXTRAS_DIR}/fbx.hpp
        )

target_include_directories(lava-extras.core INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        )

set_property(TARGET lava-extras.core PROPERTY EXPORT_NAME core)
add_library(lava-extras::core ALIAS lava-extras.core)

message(">> lava-extras::ofbx")

add_library(lava-extras.ofbx STATIC
        ${LIBLAVA_EXTRAS_DIR}/ofbx/fbx_loader.hpp
        ${LIBLAVA_EXTRAS_DIR}/ofbx/fbx_loader.cpp
        )

target_link_libraries(lava-extras.ofbx PUBLIC
        lava::resource
        lava::block
        lava-extras::core
        )

set_property(TARGET lava-extras.ofbx PROPERTY EXPORT_NAME ofbx)
add_library(lava-extras::ofbx ALIAS lava-extras.ofbx)
