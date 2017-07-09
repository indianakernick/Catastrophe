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
#include "player input component.hpp"
#include "handle input.hpp"
#include <iostream>

bool AppImpl::init() {
  SDLApp::initWindow(WINDOW_DESC, true);
  evtMan = std::make_unique<Game::EventManager>();
  actor.addComponent(std::make_shared<PlayerInputComponent>());
  actor.initComponents();
  
  return true;
}

void AppImpl::quit() {
  actor.quitComponents();
  evtMan.reset();
  SDLApp::quitWindow();
}

bool AppImpl::input(uint64_t) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      return false;
    } else {
      handleGameInput(e);
    }
  }
  return true;
}

bool AppImpl::update(const uint64_t delta) {
  evtMan->update();
  actor.updateComponents(delta);
  
  std::cout << "Player position is " << actor.pos.x << ", " << actor.pos.y << '\n';
  
  return true;
}

void AppImpl::render(uint64_t) {
  
}
