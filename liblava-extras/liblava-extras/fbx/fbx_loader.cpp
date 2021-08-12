#include "fbx_loader.hpp"

namespace lava::extras {

// TODO: Template the type of vertices here.
auto load_fbx_model_by_index(lava::device_ptr device, lava::name filename,
                             ofbx::IScene* scene, int index) -> fbx_data {
  lava::extras::fbx_data fbx_data;
  lava::mesh_data mesh_data;

  const ofbx::Mesh* mesh = scene->getMesh(index);
  const ofbx::Geometry* geom = mesh->getGeometry();
  const int vertex_count = geom->getVertexCount();
  const ofbx::Vec3* vertices = geom->getVertices();
  for (int i = 0; i < vertex_count; ++i) {
    ofbx::Vec3 v = vertices[i];
    mesh_data.vertices[i].position = lava::v3(v.x, v.y, v.z);
  }
  // TODO: Template arguments (and concepts) for loading colors, normals, and
  // UVs.

  fbx_data.mesh_data = mesh_data;
  return fbx_data;
}

}  // namespace lava::extras
