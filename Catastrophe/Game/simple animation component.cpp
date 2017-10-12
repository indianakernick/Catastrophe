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
#include "body physics component.hpp"

void SimpleAnimationComponent::init(const YAML::Node &node) {
  transform = node.as<Transform>();
  float duration = 1.0f;
  getOptional(duration, node, "duration");
  anim.setDuration(duration);
}

void SimpleAnimationComponent::update(const float delta) {
  anim.advance(delta);
  anim.repeatOnOverflow();
  const auto bodyComp
  = std::dynamic_pointer_cast<BodyPhysicsComponent>(getEntity().get<PhysicsComponent>());
  if (bodyComp) {
    transform.pos = bodyComp->getPos();
    transform.rotation = bodyComp->getAngle();
  }
  model = transform.getMat3();
}

float SimpleAnimationComponent::getProgress() const {
  return anim.getProgressTime();
}

glm::mat3 SimpleAnimationComponent::getModelMat() const {
  return model;
}
