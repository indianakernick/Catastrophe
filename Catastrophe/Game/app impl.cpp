//
//  app impl.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "app impl.hpp"

#include "player.hpp"
#include "file constants.hpp"
#include "window constants.hpp"

std::unique_ptr<AppImpl> app = nullptr;

bool AppImpl::init() {
  SDLApp::initWindow(WINDOW_DESC, WINDOW_VSYNC);
  renderingSystem.init(renderer.get(), SPRITE_SHEET_PATH);
  physicsSystem.init();
  inputSystem.init();
  entityManager.init(inputSystem, physicsSystem, renderingSystem);
  player = entityManager.create(makePlayer);
  return true;
}

void AppImpl::quit() {
  entityManager.destroy(player);
  entityManager.quit();
  inputSystem.quit();
  physicsSystem.quit();
  renderingSystem.quit();
  SDLApp::quitWindow();
}

bool AppImpl::input(uint64_t) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      return false;
    } else {
      inputSystem.handleEvent(e);
    }
  }
  return true;
}

bool AppImpl::update(const uint64_t deltaMS) {
  physicsSystem.update(deltaMS / 1000.0f);
  entityManager.update(deltaMS / 1000.0f);
  return true;
}

void AppImpl::render(const uint64_t) {
  renderer.clear();
  renderingSystem.render();
  renderer.present();
}
