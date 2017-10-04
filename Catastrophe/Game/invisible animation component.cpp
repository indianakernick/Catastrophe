//
//  invisible animation component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 4/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "invisible animation component.hpp"

const Sprite InvisibleAnimationComponent::sprite = {};
const Frame InvisibleAnimationComponent::frame = {};

InvisibleAnimationComponent::InvisibleAnimationComponent(
  const YAML::Node &,
  const YAML::Node &,
  RenderingContext &
) {}

void InvisibleAnimationComponent::update(float) {}

const Sprite &InvisibleAnimationComponent::getSprite() const {
  return sprite;
}

const Frame &InvisibleAnimationComponent::getFrame() const {
  return frame;
}

glm::mat3 InvisibleAnimationComponent::getModelMat() const {
  return {};
}
