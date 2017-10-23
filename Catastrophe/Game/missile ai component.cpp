//
//  missile ai component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 23/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "missile ai component.hpp"

#include "systems.hpp"
#include "yaml helper.hpp"
#include "player constants.hpp"
#include "body physics component.hpp"
#include "missile physics component.hpp"

void MissileAIComponent::init(const YAML::Node &node) {
  constants.maxSpeed = 1.0f;
  timeToAcc = 1.0f;
  maxAcc = 1.0f;
  getOptional(constants.maxSpeed, node, "max speed");
  getOptional(timeToAcc, node, "acceleration time");
  getOptional(maxAcc, node, "max acceleration");
}

void MissileAIComponent::update(float) {
  const auto playerComp = Systems::physics.get(PLAYER_ID).lock();
  if (!playerComp) {
    return;
  }
  const auto playerBody = std::dynamic_pointer_cast<BodyPhysicsComponent>(playerComp);
  if (!playerBody || !playerBody->getBody()) {
    return;
  }
  
  const glm::vec2 target = playerBody->getPos();
  const auto missileComp = getExpectedCompImpl<MissilePhysicsComponent>();
  const glm::vec2 missilePos = missileComp->getPos();
  const glm::vec2 missileVel = missileComp->getVel();
  
  const glm::vec2 steer = seek(constants, missilePos, target);
  acc = applySteer(missileVel, steer, timeToAcc);
  acc = clampLength(acc, maxAcc);
}

glm::vec2 MissileAIComponent::getAcc() const {
  return acc;
}
