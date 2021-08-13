#pragma once
#include <liblava/lava.hpp>

#include "../../../ext/OpenFBX/src/ofbx.h"

namespace lava::extras {

typedef struct {
  lava::mesh_data mesh_data;
} fbx_data;

auto load_fbx_scene(lava::name filename) -> ofbx::IScene*;

auto load_fbx_model(ofbx::IScene* scene) -> fbx_data;

}  // namespace lava::extras
