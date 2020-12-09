#include "app.h"
#include "game_canvas.h"
#include "test_canvas.h"

App::App() {
}

App::App(int argc, char **argv) : gBaseApp(argc, argv) {
}

App::~App() {
}

void App::setup() {
  TestCanvas* cnv = new TestCanvas(this);
  appmanager->setCurrentCanvas(cnv);
}

void App::update() {
}
