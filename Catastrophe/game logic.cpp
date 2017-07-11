//
//  game logic.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "game logic.hpp"

#include "player input component.hpp"
#include "player render component.hpp"

GameLogic::GameLogic()
  : player(1) {}

void GameLogic::init() {
  player.addComponent<InputComponent>(std::make_shared<PlayerInputComponent>());
  player.addComponent<RenderComponent>(std::make_shared<PlayerRenderComponent>());
  player.initComponents();
}

void GameLogic::quit() {
  player.quitComponents();
}

void GameLogic::handleCommand(InputCommand::Ptr command) {
  command->execute(player);
}

void GameLogic::update(const uint64_t delta) {
  player.updateComponents(delta);
  player.flushMessages();
}
