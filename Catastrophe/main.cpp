//
//  main.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "app impl.hpp"
#include "sprite test app.hpp"
#include <SDL2/SDL_messagebox.h>
#include <Simpleton/Utils/profiler.hpp>

int main(int, char **) {
  const float timeStep = 1.0f / 60.0f;
  const uint32_t maxSteps = 1;

  /*app = std::make_unique<AppImpl>();
  
  #ifdef NDEBUG
  try {
    app->mainLoop(timeStep, maxSteps);
  } catch (std::exception &e) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fatal Error", e.what(), nullptr);
    return 1;
  }
  #else
  app->mainLoop(timeStep, maxSteps);
  #endif*/
  
  SpriteTestApp test("pentagon sprite.lua", "main");
  test.mainLoop(timeStep, maxSteps);
  
  PROFILER_INFO(stdout);
  
  return 0;
}
