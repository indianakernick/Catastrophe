//
//  app impl.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "app impl.hpp"

#include "constants.hpp"
#include "handle player input.hpp"

std::unique_ptr<AppImpl> app = nullptr;

AppImpl::AppImpl()
  : fpsPrintFreq(2) {}

bool AppImpl::init() {
  SDLApp::initWindow(WINDOW_DESC, true);
  SDL_RenderSetLogicalSize(renderer.get(), WINDOW_PIXEL_SIZE.x, WINDOW_PIXEL_SIZE.y);
  fpsCounter.init();
  return true;
}

void AppImpl::quit() {
  SDLApp::quitWindow();
}

bool AppImpl::input(uint64_t) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      return false;
    } else {
      handlePlayerInput(player, e);
    }
  }
  return true;
}

bool AppImpl::update(const uint64_t deltaMS) {
  if (fpsPrintFreq.canDoOverlap()) {
    //std::cout << "FPS:   " << fpsCounter.get() << '\n';
  }
  
  player.update(deltaMS / 1000.0f);
  return true;
}

void AppImpl::render(const uint64_t) {
  fpsCounter.frame();
  renderer.clear();
  player.render(renderer.get());
  renderer.present();
}
