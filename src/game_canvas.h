#pragma once

#include "app.h"
#include "gBaseCanvas.h"
#include "gBox.h"
#include "gCamera.h"
#include "gImage.h"
#include "gPlane.h"

class GameCanvas : public gBaseCanvas {
 public:
  GameCanvas(App* root);
  virtual ~GameCanvas();

  void setup();
  void update();
  void draw();

  void keyPressed(int key);
  void keyReleased(int key);
  void charPressed(unsigned int codepoint);
  void mouseMoved(int x, int y );
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void mouseScrolled(int x, int y);
  void mouseEntered();
  void mouseExited();
  void windowResized(int w, int h);

  void showNotify();
  void hideNotify();


  void UpdateKeyboardAxis();

 private:
  App* root;
  gImage texture_;
  gCamera camera_;
  gBox box_;
  gPlane plane_;
  gFbo fbo_;
  std::unordered_map<int, bool> keys_;
  float delta_time_;
  float move_speed_ = 8.0;
  std::map<std::string, float> axis_;
  float axis_sensitivity_x_ = 2.0f;
  float axis_sensitivity_y_ = 2.0f;
  float axis_limit_y_ = PI / 2.0f - (PI / 16.0f);
  bool camera_active_ = true;
};
