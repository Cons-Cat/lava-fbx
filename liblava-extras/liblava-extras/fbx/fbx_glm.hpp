#pragma once

#include <glm/mat4x4.hpp>

#include "../../../ext/OpenFBX/src/ofbx.h"

namespace lava::extras {

auto fbx_mat_to_glm_dmat(ofbx::Matrix fbx_mat) -> glm::dmat4;

auto fbx_mat_to_glm_mat(ofbx::Matrix fbx_mat) -> glm::mat4;

}  // namespace lava::extras
