#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "gGLFWWindow.h"
#include "game_canvas.h"

GameCanvas::GameCanvas(App* root) : gBaseCanvas(root) {
  this->root = root;
}

GameCanvas::~GameCanvas() {
}

void GameCanvas::setup() {
  appmanager->setTargetFramerate(INTMAX_MAX);

  camera_active_ = false;
  texture_.loadImage("babanne.png");
  texture_.setFiltering(gTexture::TEXTUREMINMAGFILTER_NEAREST, gTexture::TEXTUREMINMAGFILTER_NEAREST);
  plane_.setTexture(&texture_);
  plane_.setPosition(0, 1, -10);
  plane_.setScale(5, 5, 5);
  camera_.setPosition(0, 0, 0);
  camera_.panDeg(35);
  fbo_.allocate(320, 240);
  fbo_.getTexture().setFiltering(gTexture::TEXTUREMINMAGFILTER_NEAREST, gTexture::TEXTUREMINMAGFILTER_NEAREST);

  axis_["Horizontal"] = 0.0f;
  axis_["Vertical"] = 0.0f;
  axis_["Mouse X"] = 0.0f;
  axis_["Mouse Y"] = 0.0f;

  G_CHECK_GL(glEnable(GL_DEPTH_TEST));
  G_CHECK_GL(glFrontFace(GL_CW));
  G_CHECK_GL(glCullFace(GL_BACK));
  renderer->enableAlphaBlending();
}

void GameCanvas::update() {
  delta_time_ = appmanager->getElapsedTime();
  UpdateKeyboardAxis();
  float axis_x = axis_["Horizontal"];
  float axis_y = axis_["Vertical"];
  glm::vec3 pos = camera_.getPosition();
  auto& transform = camera_.getTransformationMatrix();
  pos += glm::vec3(-transform[2]) * delta_time_ * move_speed_ * axis_y;
  pos += glm::vec3(transform[0]) * delta_time_ * move_speed_ * axis_x;
  pos.y = camera_.getPosY();
  camera_.setPosition(pos);
  float input_x = axis_["Mouse X"];
  float input_y = axis_["Mouse Y"];
  camera_.setOrientation(glm::quat{glm::vec3{input_y, input_x, 0.0f}});
}

void GameCanvas::draw() {
  enableDepthTest();
  fbo_.bind();
  clearColor(30, 30, 30);
  G_CHECK_GL(glEnable(GL_CULL_FACE));
  camera_.begin();
  plane_.draw();
  camera_.end();
  fbo_.unbind();
  G_CHECK_GL(glDisable(GL_CULL_FACE));
  fbo_.draw(0, 0, getWidth(), getHeight());
  disableDepthTest();

}

void GameCanvas::keyPressed(int key) {
  keys_[key] = true;
}

void GameCanvas::keyReleased(int key) {
  keys_[key] = false;
  if (key == G_KEY_ESC) {
    if (!camera_active_) {
      appmanager->getWindow()->setCursorMode(gGLFWWindow::CURSORMODE_HIDDEN);
      camera_active_ = true;
    } else {
      appmanager->getWindow()->setCursorMode(gGLFWWindow::CURSORMODE_NORMAL);
      camera_active_ = false;
    }
  }
}

void GameCanvas::charPressed(unsigned int codepoint) {
}

void GameCanvas::mouseMoved(int x, int y) {
  if (!camera_active_) {
    return;
  }
  float width = getScreenWidth();
  float height = getScreenHeight();
  appmanager->getWindow()->setCursorPos(width / 2.0f, height / 2.0f);
  axis_["Mouse X"] += axis_sensitivity_x_ * (((width / 2.0f) - x) / width);
  axis_["Mouse Y"] += axis_sensitivity_y_ * (((height / 2.0f) - y) / width);
  axis_["Mouse Y"] = std::clamp(
      axis_["Mouse Y"], -axis_limit_y_,
      axis_limit_y_);
}

void GameCanvas::mouseDragged(int x, int y, int button) {
  mouseMoved(x, y);
}

void GameCanvas::mousePressed(int x, int y, int button) {
}

void GameCanvas::mouseReleased(int x, int y, int button) {
}

void GameCanvas::mouseScrolled(int x, int y) {
}

void GameCanvas::mouseEntered() {
}

void GameCanvas::mouseExited() {
}

void GameCanvas::windowResized(int w, int h) {
}

void GameCanvas::showNotify() {

}

void GameCanvas::hideNotify() {

}

void GameCanvas::UpdateKeyboardAxis() {
  bool right = keys_[G_KEY_D];
  bool left = keys_[G_KEY_A];
  bool up = keys_[G_KEY_W];
  bool down = keys_[G_KEY_S];

  if (right && !left) {
    axis_["Horizontal"] = 1;
  } else if (!right && left) {
    axis_["Horizontal"] = -1;
  } else {
    axis_["Horizontal"] = 0;
  }

  if (up && !down) {
    axis_["Vertical"] = 1;
  } else if (!up && down) {
    axis_["Vertical"] = -1;
  } else {
    axis_["Vertical"] = 0;
  }
}