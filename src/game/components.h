
#pragma once

#include "glm/glm.hpp"
#include "gMesh.h"

struct TransformComponent {
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;
};

struct TagComponent {
  TagComponent(const std::string& tag) : tag(std::move(tag)) {}

  std::string tag;
};

class Mesh : public gMesh {
 public:
  Mesh() : gMesh() {}
  Mesh(std::vector<gVertex> vertices, std::vector<gIndex> indices, std::vector<gTexture*> textures) :
     gMesh(vertices, indices, textures) {}

  void setTransform(const TransformComponent& transform) {
    position = transform.position;
    orientation = glm::quat(transform.rotation);
    scalevec = transform.scale;
  }

};
struct MeshComponent {
  Mesh mesh;
  glm::vec3 normal;
};