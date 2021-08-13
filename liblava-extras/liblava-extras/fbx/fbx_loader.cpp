#include "fbx_loader.hpp"

namespace lava::extras {

auto load_fbx_scene(lava::name filename) -> ofbx::IScene* {
  string target_file = filename;
  // lava::cdata const file_data = lava::file_data(filename);
  // TODO(conscat): Modernize C-style casts.
  FILE* fp = fopen(filename, "rb");

  if (!fp) return nullptr;

  fseek(fp, 0, SEEK_END);
  long file_size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  auto* content = new ofbx::u8[file_size];
  fread(content, 1, file_size, fp);

  // ofbx::u8 const* fbx_data = reinterpret_cast<ofbx::u8
  // const*>(file_data.ptr);
  auto* scene = ofbx::load((ofbx::u8*)content, file_size,
                           (ofbx::u64)ofbx::LoadFlags::TRIANGULATE);
  // auto* scene = ofbx::load((ofbx::u8*)fbx_data, file_data.size,
  //                          (ofbx::u64)ofbx::LoadFlags::TRIANGULATE);

  // ofbx::IScene* scene = ofbx::load(
  //     fbx_data, file_data.size,
  //     static_cast<ofbx::u64>(ofbx::LoadFlags::TRIANGULATE));
  return scene;
}

// TODO(conscat): Template the type of vertices here.
auto load_fbx_model_by_index(ofbx::IScene* scene, int index) -> fbx_data {
  lava::extras::fbx_data fbx_data;
  lava::mesh_data mesh_data;

  const ofbx::Mesh* mesh = scene->getMesh(index);
  const ofbx::Geometry* geom = mesh->getGeometry();
  const int fbx_vertex_count = geom->getVertexCount();
  const ofbx::Vec3* fbx_vertices = geom->getVertices();
  for (int i = 0; i < fbx_vertex_count; ++i) {
    ofbx::Vec3 v = fbx_vertices[i];
    lava::vertex lava_vertex{.position = lava::v3(v.x, v.y, v.z)};
    mesh_data.vertices.push_back(lava_vertex);
  }
  const int* indices = geom->getFaceIndices();
  int index_count = geom->getIndexCount();
  for (int i = 0; i < index_count; i++) {
    // Negative indices represent the end of a polygon. They must be inverted
    // and decremented.
    int index = (indices[i] < 0) ? (-indices[i] - 1) : indices[i];
    mesh_data.indices.push_back(index); // cast to `lava::index`
  }
  // TODO(conscat): Template arguments (and concepts) for loading colors,
  // normals, and UVs.
  fbx_data.mesh_data = mesh_data;
  return fbx_data;
}

auto load_fbx_models(ofbx::IScene* scene) -> std::vector<fbx_data> {
  std::vector<fbx_data> fbx;
  for (size_t i = 0; i < scene->getMeshCount(); i++) {
    fbx.push_back(load_fbx_model_by_index(scene, i));
  }
  return fbx;
}

}  // namespace lava::extras
