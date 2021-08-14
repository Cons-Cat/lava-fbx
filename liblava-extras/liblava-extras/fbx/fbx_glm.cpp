#include <liblava-extras/fbx/fbx_glm.hpp>

namespace lava::extras {

auto fbx_mat_to_glm_dmat(ofbx::Matrix fbx_mat) -> glm::dmat4 {
  // Both ofbx::Matrix and glm::dmat4 are column-major 4x4 matrices of
  // double-precision floating point numbers.
  /* NOTE: `std::bitcast<>()` is currently
   * supported on g++11. Liblava officially supports g++10, so
   * `reinterpret_cast<>()` is used instead. */
  // NOLINTNEXTLINE
  glm::dmat4 dmat = *reinterpret_cast<glm::dmat4*>(&fbx_mat);
  return dmat;
}

auto fbx_mat_to_glm_mat(ofbx::Matrix fbx_mat) -> glm::mat4 {
  return static_cast<glm::mat4>(lava::extras::fbx_mat_to_glm_dmat(fbx_mat));
}

}  // namespace lava::extras
