//
//  ground droid animation component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "ground droid animation component.hpp"

#include "yaml helper.hpp"
#include "body physics component.hpp"
#include "../Libraries/Box2D/Dynamics/b2Body.h"

void GroundDroidAnimationComponent::init(const YAML::Node &node) {
  transform = node.as<Transform>();
}

void GroundDroidAnimationComponent::update(const float delta) {
  const auto bodyComp = getExpectedCompImpl<const BodyPhysicsComponent>();
  const b2Body *const body = bodyComp->getBody();
  //I don't think there's any point in getting the velocity relative to the
  //ground like PlayerPhysicsComponent does.
  const float velX = body->GetLinearVelocity().x;
  progress += velX * 0.1f * delta;
  progress = std::fmod(progress, 1.0f);
  
  transform.pos = bodyComp->getPos();
  mat = transform.getMat3();
  dirX.getDir(velX);
}

float GroundDroidAnimationComponent::getProgress() const {
  return progress;
}

glm::mat3 GroundDroidAnimationComponent::getModelMat() const {
  return mat;
}

float GroundDroidAnimationComponent::getDir() const {
  return dirX.getDir();
}
