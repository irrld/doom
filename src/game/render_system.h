
#pragma once

class Scene;
class RenderSystem {
 public:
  RenderSystem(Scene* scene);
  ~RenderSystem() = default;

  void Update(double delta);
 private:
  Scene* scene_;

};