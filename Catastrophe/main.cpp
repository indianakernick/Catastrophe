//
//  main.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "app impl.hpp"

#include <SDL2/SDL_messagebox.h>

int main(int, char **) {
  app = std::make_unique<AppImpl>();
  try {
    app->mainLoop(1.0f / 60.0f, 16);
  } catch (std::exception &e) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fatal Error", e.what(), nullptr);
    return 1;
  }
  return 0;
}
