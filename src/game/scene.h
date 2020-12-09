#pragma once

#include "gTexture.h"
#include "json.hpp"
#include "render_system.h"
#include "util.h"

using ObjectId = uint64_t;
using SectionId = uint16_t;

class Section {
 public:
  Section(SectionId id, const std::string& name) : id_(id), name_(name) {}

  SectionId id() const {
    return id_;
  }

  const std::string& name() const {
    return name_;
  }

  void AddObject(ObjectId id) {
    objects_.push_back(id);
  }

  const std::vector<ObjectId>& objects() const {
    return objects_;
  }

 private:
  SectionId id_;
  std::string name_;
  std::vector<ObjectId> objects_;

};

class Scene {
 public:
  Scene(const std::string& file_name);

  void Load();

  void Update(double delta);

  ObjectId CreateObject() {
    ObjectId id = object_id_counter_++;
    components_[id] = std::unordered_map<size_t, void*>();
    return id;
  }

  void RemoveObject(ObjectId id) {
    components_.erase(id);
  }

  template <typename T>
  T& GetComponent(ObjectId id) {
    return *static_cast<T*>(components_[id][typeid(T).hash_code()]);
  }

  template <typename T, typename... Args>
  void AddComponent(ObjectId id, Args&& ...args) {
    components_[id][typeid(T).hash_code()] = new T(std::forward<Args>(args)...);
  }

  template <typename T>
  void RemoveComponent(ObjectId id) {
    components_[id].erase(typeid(T).hash_code());
  }

  template <typename T>
  bool HasComponent(ObjectId id) {
    return components_[id].find(typeid(T).hash_code()) != components_[id].end();
  }

  const std::unordered_map<SectionId, Ref<Section>>& sections() const {
    return sections_;
  }
 private:
  std::string file_name_;
  std::string level_name_;
  ObjectId object_id_counter_;
  SectionId section_id_counter_;
  std::unordered_map<SectionId, Ref<Section>> sections_;
  std::unordered_map<ObjectId, std::unordered_map<size_t, void*>> components_;

  Ref<RenderSystem> render_system_;

 private:
  glm::vec3 ReadVec3(const nlohmann::json& j) {
    return glm::vec3(j["x"], j["y"], j["z"]);
  }
};

class Object {
 public:
  Object(Scene* scene, ObjectId id) : scene_(scene), id_(id) {}

  template <typename T>
  T& GetComponent() {
    return scene_->GetComponent<T>(id_);
  }

  template <typename T, typename... Args>
  T& AddComponent(Args&& ...args) {
    scene_->AddComponent<T>(id_, std::forward<Args>(args)...);
    return GetComponent<T>();
  }

  template <typename T>
  void RemoveComponent() {
    scene_->RemoveComponent<T>(id_);
  }

  template <typename T>
  bool HasComponent() {
    return scene_->HasComponent<T>(id_);
  }
 private:
  ObjectId id_;
  Scene* scene_;
};
