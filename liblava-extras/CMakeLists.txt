cmake_minimum_required(VERSION 3.20)
project(liblava-extras LANGUAGES C CXX)

set(LIBLAVA_EXTRAS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/liblava-extras)

message(">> lava-extras::fbx")

set(OFBX_SRC ${CMAKE_CURRENT_SOURCE_DIR}/../ext/OpenFBX/src)
add_library(
  lava-extras.fbx STATIC
  ${OFBX_SRC}/miniz.h
  ${OFBX_SRC}/miniz.c
  ${OFBX_SRC}/ofbx.h
  ${OFBX_SRC}/ofbx.cpp
  ${LIBLAVA_EXTRAS_DIR}/fbx/fbx_glm.hpp
  ${LIBLAVA_EXTRAS_DIR}/fbx/fbx_glm.cpp
  ${LIBLAVA_EXTRAS_DIR}/fbx/fbx_loader.hpp
  ${LIBLAVA_EXTRAS_DIR}/fbx/fbx_loader.cpp
  ${LIBLAVA_EXTRAS_DIR}/fbx.hpp
)

target_link_libraries(
  lava-extras.fbx PUBLIC
  # TODO: Only link the lava modules that are used.
  lava::app
)

target_include_directories(
  lava-extras.fbx PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

set_property(TARGET lava-extras.fbx PROPERTY EXPORT_NAME fbx)
add_library(lava-extras::fbx ALIAS lava-extras.fbx)
