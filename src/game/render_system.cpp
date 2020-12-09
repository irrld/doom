
#pragma once

#include "render_system.h"
#include "components.h"
#include "scene.h"

RenderSystem::RenderSystem(Scene* scene) : scene_(scene) {

}

void RenderSystem::Update(double delta) {
  for (const auto& entry : scene_->sections()) {
    auto section_id = entry.first;
    auto section = entry.second;
    for (const auto& object_id : section->objects()) {
      Object object{scene_, object_id};
      if (object.HasComponent<MeshComponent>()) {
        auto& mesh = object.GetComponent<MeshComponent>();
        auto& transform = object.GetComponent<TransformComponent>();
        mesh.mesh.setTransform(transform);
        mesh.mesh.draw();
      }
    }
  }
}