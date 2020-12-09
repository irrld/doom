#include "test_canvas.h"

void TestCanvas::setup() {
  setupGUI();
}

void TestCanvas::update() {
  barfill += appmanager->getElapsedTime();
  if (barfill > 1.0f) {
    barfill = 0.0f;
  }
}

void TestCanvas::draw() {
  const gColor& oldcolor = getColor();
  gDrawRectangle(barx, bary, barw, barh, true);
  setColor(255, 0, 0);
  gDrawRectangle(barfillx, barfilly, barfillw * barfill, barfillh, true);
  setColor(oldcolor);
}

void TestCanvas::windowResized(int w, int h) {
  setupGUI();
}

void TestCanvas::setupGUI() {
  renderer->setProjectionMatrix2d(glm::ortho(0.0f, (float)getScreenWidth(), (float)getScreenHeight(), 0.0f, -1.0f, 1.0f));
  scale = std::min(getScreenWidth() / 1280.0f, getScreenHeight() / 720.0f);
  if (scale < 1.0f) {
    scale = 1.0f;
  }
  gLogi("TestCanvas") << scale;
  int screen_safe_zone = 50; // 50 points
  barw = 200 * scale;
  barh = 10 * scale;
  barx = getScreenWidth() - barw - (screen_safe_zone * scale);
  bary = getScreenHeight() - barh - (screen_safe_zone * scale);
  float bar_padding = 2 * scale;
  barfillx = barx + bar_padding;
  barfilly = bary + bar_padding;
  barfillw = barw - bar_padding * 2;
  barfillh = barh - bar_padding * 2;
}
