//
//  turret animation component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 14/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "turret animation component.hpp"

#include "entity.hpp"
#include "yaml helper.hpp"
#include "systems registry.hpp"
#include "turret physics component.hpp"

void TurretAnimationComponent::init(const YAML::Node &node) {
  transform = node.as<Transform>();
}

void TurretAnimationComponent::update(float) {
  const auto turretComp = getExpectedCompImpl<const TurretPhysicsComponent>();
  transform.pos = turretComp->getPos();
  transform.rotation = turretComp->getAngle();
  model = transform.getMat3();
}

float TurretAnimationComponent::getProgress() const {
  return 0.0f;
}

glm::mat3 TurretAnimationComponent::getModelMat() const {
  return model;
}
