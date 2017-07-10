//
//  game logic.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "game logic.hpp"

#include "player input component.hpp"
#include "handle input.hpp"

void GameLogic::init() {
  player.addComponent(std::make_shared<PlayerInputComponent>());
  player.initComponents();
}

void GameLogic::quit() {
  player.quitComponents();
}

void GameLogic::handleInput(const SDL_Event &event) {
  handleGameInput(event);
}

void GameLogic::update(const uint64_t delta) {
  player.updateComponents(delta);
  player.flushMessages();
}
