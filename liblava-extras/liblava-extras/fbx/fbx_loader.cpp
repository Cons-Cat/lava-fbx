#include "fbx_loader.hpp"

namespace lava::extras {

auto load_fbx_scene(lava::name filename) -> ofbx::IScene* {
  string target_file = filename;
  lava::cdata const data = lava::file_data(filename);
  // TODO: Modernize C-style casts.
  ofbx::IScene* scene = ofbx::load((ofbx::u8*)data.ptr, data.size,
                                   (ofbx::u64)ofbx::LoadFlags::TRIANGULATE);
  return scene;
}

// TODO: Template the type of vertices here.
auto load_fbx_model_by_index(ofbx::IScene* scene, int index) -> fbx_data {
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
