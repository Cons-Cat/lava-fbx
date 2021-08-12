cmake_minimum_required(VERSION 3.20)

project(liblava-extras LANGUAGES CXX)

# set(LIBLAVA_EXTRAS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/liblava-extras)
set(LIBLAVA_EXTRAS_DIR ${CMAKE_CURRENT_SOURCE_DIR})

message(">> lava-extras::ofbx")

add_library(lava-extras.ofbx STATIC
        ${LIBLAVA_EXTRAS_DIR}/ofbx/fbx_loader.hpp
        ${LIBLAVA_EXTRAS_DIR}/ofbx/fbx_loader.cpp
        )

target_link_libraries(lava-extras.ofbx PUBLIC
        lava::resource
        )

set_property(TARGET lava-extras.ofbx PROPERTY EXPORT_NAME ofbx)
add_library(lava-extras::ofbx ALIAS lava-extras.ofbx)
