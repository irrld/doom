#pragma once

#include "scene.h"
#include <fstream>
#include "components.h"

using namespace nlohmann;

Scene::Scene(const std::string& file_name) : file_name_(file_name) {
  object_id_counter_ = 0;
}

void Scene::Load() {
  std::ifstream file("Test.json");
  json j = json::parse(file);
  level_name_ = j["level_name"];
  for (const auto& item : j["sections"]) {
    std::string section_name = item["section_name"];

    SectionId section_id = section_id_counter_++;
    Ref<Section> section = CreateRef<Section>(section_id, section_name);
    sections_[section_id] = section;

    for (const auto& object_item : item["objects"]) {
      ObjectId id = CreateObject();
      section->AddObject(id);

      Object object{this, id};
      for (const auto& component_item : object_item["components"]) {
        std::string type = component_item["type"];
        if (type == "TransformComponent") {
          auto& transform = object.AddComponent<TransformComponent>();
          transform.position = ReadVec3(component_item["pos"]);
          transform.rotation = ReadVec3(component_item["rot"]);
          transform.scale = ReadVec3(component_item["scale"]);
        } else if (type == "TagComponent") {
          std::string tag = component_item["tag"];
          object.AddComponent<TagComponent>(tag);
        }
      }
    }
  }
}

void Scene::Update(double delta) {
  render_system_->Update(delta);
}