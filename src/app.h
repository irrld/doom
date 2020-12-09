#pragma once

#include "gBaseApp.h"


class App : public gBaseApp {
 public:
  App();
  App(int argc, char **argv);
  ~App();

  void setup();
  void update();
};
