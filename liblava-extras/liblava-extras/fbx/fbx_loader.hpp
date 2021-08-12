#pragma once
#include <liblava/lava.hpp>

namespace lava::extras {
#include "../../../ext/OpenFBX/src/ofbx.h"

typedef struct {
  lava::mesh_data mesh_data;
} fbx_data;

auto load_fbx_model_by_index(lava::device_ptr device, lava::name filename,
                             ofbx::IScene* scene, int index) -> fbx_data;

}  // namespace lava::extras
