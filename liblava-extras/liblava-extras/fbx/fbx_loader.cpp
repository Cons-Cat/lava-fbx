#include <liblava-extras/fbx/fbx_glm.hpp>
#include <liblava-extras/fbx/fbx_loader.hpp>

namespace lava::extras {

auto load_fbx_scene(lava::name filename) -> ofbx::IScene* {
  std::string target_file = filename;
  // lava::cdata const file_data = lava::file_data(filename);
  // TODO(conscat): Modernize C-style casts.
  FILE* fp = fopen(filename, "rb");
  if (fp == nullptr) {
    return nullptr;
  }

  fseek(fp, 0, SEEK_END);
  lava::int64 file_size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  unsigned char* content = new ofbx::u8[file_size];
  fread(content, 1, file_size, fp);

  // ofbx::u8 const* fbx_data = reinterpret_cast<ofbx::u8
  // const*>(file_data.ptr);
  auto* scene =
      ofbx::load(static_cast<ofbx::u8*>(content), file_size,
                 static_cast<ofbx::u64>(ofbx::LoadFlags::TRIANGULATE));
  // auto* scene = ofbx::load((ofbx::u8*)fbx_data, file_data.size,
  //                          (ofbx::u64)ofbx::LoadFlags::TRIANGULATE);

  // ofbx::IScene* scene = ofbx::load(
  //     fbx_data, file_data.size,
  //     static_cast<ofbx::u64>(ofbx::LoadFlags::TRIANGULATE));
  return scene;
}

// TODO(conscat): Template the type of vertices here.
auto load_fbx_model(ofbx::IScene* scene) -> fbx_data {
  lava::extras::fbx_data fbx_data;
  lava::mesh_data mesh_data;
  int indices_offset = 0;
  int mesh_count = scene->getMeshCount();
  for (int i = 0; i < mesh_count; i++) {
    const ofbx::Mesh* mesh = scene->getMesh(i);
    auto mesh_transform_global = mesh->getGlobalTransform();
    const ofbx::Geometry* geom = mesh->getGeometry();
    const int vertex_count = geom->getVertexCount();
    const ofbx::Vec3* fbx_vertices = geom->getVertices();
    for (int i = 0; i < vertex_count; ++i) {
      ofbx::Vec3 v = fbx_vertices[i];
      glm::vec4 transformed_position =
          lava::extras::fbx_mat_to_glm_mat(mesh_transform_global) *
          glm::vec4(v.x, v.y, v.z, 1);
      lava::vertex lava_vertex{.position = glm::vec3(transformed_position.x,
                                                     -transformed_position.y,
                                                     transformed_position.z)};
      mesh_data.vertices.push_back(lava_vertex);
    }
    const int* indices = geom->getFaceIndices();
    int index_count = geom->getIndexCount();
    for (int j = 0; j < index_count; j++) {
      // Negative indices represent the end of a polygon. They must be inverted
      // and decremented.
      int index = (indices[j] < 0) ? (-indices[j] - 1) : indices[j];
      mesh_data.indices.push_back(index +
                                  indices_offset);  // cast to `lava::index`
    }
    indices_offset += vertex_count;
  }
  // TODO(conscat): Template arguments (and concepts) for loading colors,
  // normals, and UVs.
  fbx_data.mesh_data = mesh_data;
  return fbx_data;
}

}  // namespace lava::extras
