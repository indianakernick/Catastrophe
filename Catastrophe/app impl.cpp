//
//  app impl.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "app impl.hpp"

#include "constants.hpp"
#include <Simpleton/Event/manager.hpp>
#include "register factory functions.hpp"
#include <Simpleton/Platform/system info.hpp>

std::unique_ptr<AppImpl> app = nullptr;

AppImpl::AppImpl()
  : factory(entityMan, localViewMan, localControllerMan) {}

bool AppImpl::init() {
  SDLApp::initWindow(WINDOW_DESC, true);
  localViewMan.init(renderer.get(), SPRITE_SHEET_PATH);
  
  registerFactoryFunctions(factory);
  
  playerID = factory.make("player", {});
  
  return true;
}

void AppImpl::quit() {
  factory.destroy(playerID);

  localViewMan.quit();
  SDLApp::quitWindow();
}

bool AppImpl::input(uint64_t) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      return false;
    } else {
      localControllerMan.handleEvent(e);
    }
  }
  return true;
}

bool AppImpl::update(const uint64_t delta) {
  entityMan.update(delta);
  
  return true;
}

void AppImpl::render(const uint64_t delta) {
  renderer.clear();
  localViewMan.render(delta);
  renderer.present();
}
