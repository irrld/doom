#pragma once

#include "app.h"
#include "gBaseCanvas.h"
#include "gBox.h"
#include "gCamera.h"
#include "gImage.h"
#include "gPlane.h"

class TestCanvas : public gBaseCanvas {
 public:
  TestCanvas(App* root) : gBaseCanvas(root) {
    this->root = root;
  }
  virtual ~TestCanvas() {}

  void setup();
  void update();
  void draw();

  void keyPressed(int key) {}
  void keyReleased(int key) {}
  void charPressed(unsigned int codepoint) {}
  void mouseMoved(int x, int y) {}
  void mouseDragged(int x, int y, int button) {}
  void mousePressed(int x, int y, int button) {}
  void mouseReleased(int x, int y, int button) {}
  void mouseScrolled(int x, int y) {}
  void mouseEntered() {}
  void mouseExited() {}
  void windowResized(int w, int h);

  void showNotify() {}
  void hideNotify() {}

 private:
  App* root;
  float scale = 1;
  float barx;
  float bary;
  float barw;
  float barh;
  float barfill;
  float barfillx;
  float barfilly;
  float barfillw;
  float barfillh;

  void setupGUI();
};
