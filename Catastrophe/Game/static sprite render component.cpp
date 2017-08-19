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
    rect(0.0f, 0.0f, width, height) {}

void StaticSpriteRenderComponent::update(Entity *entity, const float) {
  const b2Vec2 pos = entity->getPos();
  rect.c = {pos.x, pos.y};
}

void StaticSpriteRenderComponent::render(RenderingContext &context) {
  context.renderSprite(sprite, static_cast<Rect>(rect));
}

const CameraTarget *StaticSpriteRenderComponent::getCameraTarget() const {
  return &rect;
}
