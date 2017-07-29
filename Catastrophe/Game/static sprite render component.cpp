//
//  static sprite render component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "static sprite render component.hpp"

#include "entity.hpp"
#include "rendering context.hpp"

StaticSpriteRenderComponent::StaticSpriteRenderComponent(
  const std::string &sprite,
  const float width,
  const float height
) : sprite(sprite),
    rect({}, {width, height}) {}

void StaticSpriteRenderComponent::update(Entity *entity, const float) {
  const b2Vec2 pos = entity->getPos();
  rect.p = {pos.x, pos.y};
}

void StaticSpriteRenderComponent::render(RenderingContext &context) {
  context.renderSprite(sprite, rect);
}
