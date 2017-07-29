//
//  player render component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "player render component.hpp"

#include "entity.hpp"
#include "player constants.hpp"
#include "rendering context.hpp"

void PlayerRenderComponent::update(Entity *entity, const float) {
  const b2Vec2 pos = entity->getPos();
  rect = {
    {pos.x, pos.y},
    {PLAYER_WIDTH, PLAYER_HEIGHT}
  };
}

void PlayerRenderComponent::render(RenderingContext &context) {
  context.renderSprite("rat", rect);
}
