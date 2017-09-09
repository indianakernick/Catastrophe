//
//  vector sprite render component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 3/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "vector sprite render component.hpp"

#include "entity.hpp"
#include "vector file.hpp"
#include <glm/gtx/matrix_transform_2d.hpp>
#include "vector render.hpp"
#include "rendering context.hpp"
#include <Simpleton/Platform/system info.hpp>

VectorSpriteRenderComponent::VectorSpriteRenderComponent(
  const std::experimental::string_view spritePath,
  const float width,
  const float height
) : sprite(loadSprite((Platform::getResDir() + spritePath.data()).c_str())),
    rect(0.0f, 0.0f, width, height) {}

void VectorSpriteRenderComponent::update(Entity *entity, const float delta) {
  const b2Vec2 pos = entity->getPos();
  rect.c = {pos.x, pos.y};
  animProgress += delta * animSpeed;
  if (!animName.empty()) {
    const float duration = sprite.animations.at(animName).durationSec;
    animProgress = std::fmod(animProgress, duration);
  }
}

void VectorSpriteRenderComponent::render(NVGcontext *context) {
  if (!animName.empty()) {
    glm::mat3 transform = glm::translate({}, rect.c);
    transform = glm::scale(transform, scale);
    renderSprite(
      context,
      sprite,
      animName,
      transform,
      animProgress
    );
  }
}

const CameraMotionTarget *VectorSpriteRenderComponent::getCameraTarget() const {
  return &rect;
}

void VectorSpriteRenderComponent::setProgress(const float newProgress) {
  animProgress = newProgress;
}

void VectorSpriteRenderComponent::setSpeed(const float newSpeed) {
  animSpeed = newSpeed;
}

void VectorSpriteRenderComponent::setAnimName(const std::experimental::string_view newAnimName) {
  animName.assign(newAnimName.data(), newAnimName.size());
}

void VectorSpriteRenderComponent::setScale(const glm::vec2 newScale) {
  scale = newScale;
}
