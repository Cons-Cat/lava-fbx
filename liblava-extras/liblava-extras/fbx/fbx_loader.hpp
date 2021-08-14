#pragma once
#include <liblava/file.hpp>
#include <liblava/resource.hpp>

#include "../../../ext/OpenFBX/src/ofbx.h"

namespace lava::extras {

struct fbx_data {
  lava::mesh_data mesh_data;
};

auto load_fbx_scene(lava::name filename) -> ofbx::IScene*;

auto load_fbx_model(ofbx::IScene* scene) -> fbx_data;

}  // namespace lava::extras
