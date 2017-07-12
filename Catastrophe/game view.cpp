//
//  game view.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "game view.hpp"

void GameView::createSprite(
  const ActorID id,
  const std::string &name,
  const glm::vec2 pos,
  const glm::vec2 size
) {
  sprites.insert({id, {name, pos, size}});
}

void GameView::destroySprite(const ActorID id) {
  sprites.erase(id);
}
