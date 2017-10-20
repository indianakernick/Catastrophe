//
//  camera window size.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 27/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera window size.hpp"

#include <SDL2/SDL_video.h>

NoWindowAttached::NoWindowAttached()
  : std::logic_error("Tried to get the size of the window but the window was not attached") {}

glm::ivec2 CameraWindowSize::get() const {
  return {1280, 720};
  /*if (window == nullptr) {
    throw NoWindowAttached();
  } else {
    glm::ivec2 size;
    SDL_GetWindowSize(window, &size.x, &size.y);
    return size;
  }*/
}

void CameraWindowSize::attachWindow(SDL_Window *newWindow) {
  window = newWindow;
}

void CameraWindowSize::detachWindow() {
  window = nullptr;
}
