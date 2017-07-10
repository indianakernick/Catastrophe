//
//  app impl.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "app impl.hpp"

#include "constants.hpp"
#include <Simpleton/Platform/system info.hpp>
#include <Simpleton/Event/manager.hpp>

bool AppImpl::init() {
  SDLApp::initWindow(WINDOW_DESC, true);
  evtMan = std::make_unique<Game::EventManager>();
  view.init(renderer.get(), Platform::getResDir() + SPRITE_SHEET_PATH);
  logic.init();
  
  return true;
}

void AppImpl::quit() {
  logic.quit();
  view.quit();
  evtMan.reset();
  SDLApp::quitWindow();
}

bool AppImpl::input(uint64_t) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      return false;
    } else {
      logic.handleInput(e);
    }
  }
  evtMan->update();
  return true;
}

bool AppImpl::update(const uint64_t delta) {
  logic.update(delta);
  
  evtMan->update();
  return true;
}

void AppImpl::render(const uint64_t delta) {
  view.render(delta);
}
