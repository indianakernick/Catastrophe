//
//  simple animation component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 17/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "simple animation component.hpp"

#include "entity.hpp"
#include "yaml helper.hpp"
#include "vector file.hpp"
#include "vector render.hpp"
#include "systems registry.hpp"
#include "physics component.hpp"

SimpleAnimationComponent::SimpleAnimationComponent(
  const YAML::Node &node,
  const YAML::Node &level
) {
  transform.scale = getChild(level, "scale").as<glm::vec2>();
  float duration = 1.0f;
  getOptional(duration, node, "duration");
  anim.setDuration(duration);
}

void SimpleAnimationComponent::update(const float delta) {
  anim.advance(delta);
  anim.repeatOnOverflow();
  transform.pos = getEntity().physics->getPos();
  transform.rotation = getEntity().physics->getAngle();
  model = transform.getMat3();
}

float SimpleAnimationComponent::getProgress() const {
  return anim.getProgressTime();
}

glm::mat3 SimpleAnimationComponent::getModelMat() const {
  return model;
}
