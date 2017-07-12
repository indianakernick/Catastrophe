//
//  game logic.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "game logic.hpp"

#include "simple entity.hpp"

void GameLogic::init() {
  player = std::make_unique<SimpleEntity>(1, Rect({0, 0}, {1, 1}), 1);
}

void GameLogic::quit() {
  player.reset();
}

void GameLogic::update(const uint64_t delta) {
  player->update(delta);
}
