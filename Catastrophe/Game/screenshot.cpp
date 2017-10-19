//
//  screenshot.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 26/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "screenshot.hpp"

#include <SDL2/SDL_events.h>
#include "tinyfiledialogs.h"
#include "rendering context.hpp"
#include "framebuffer to png.hpp"

Screenshot::Screenshot()
  : framebuffer(std::make_unique<uint8_t []>(MAX_FRAMEBUFFER_SIZE)) {}

bool Screenshot::handleEvent(const SDL_Event &e) {
  if (
    e.type == SDL_KEYDOWN
    && e.key.repeat == 0
    && e.key.keysym.scancode == SDL_SCANCODE_P
  ) {
    takeScreenshot = true;
    return true;
  } else {
    return false;
  }
}

void Screenshot::postRender(RenderingContext &renderer, const bool renderFPS) {
  if (takeScreenshot) {
    takeScreenshot = false;
    renderer.postRender(
      false,
      framebuffer.get(),
      MAX_FRAMEBUFFER_SIZE
    );
    
    const char *filePath = tinyfd_saveFileDialog(
      "Save screenshot",
      "Screenshot.png",
      0,
      nullptr,
      "Image"
    );
    if (filePath != nullptr) {
      framebufferToPNG(
        filePath,
        renderer.getFramebufferSize(),
        framebuffer.get()
      );
    }
  } else {
    renderer.postRender(renderFPS);
  }
}
