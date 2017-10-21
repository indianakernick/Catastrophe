//
//  ground 0 droid ai component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "ground 0 droid ai component.hpp"

#include "yaml helper.hpp"
#include "ground droid physics component.hpp"

void Ground0DroidAIComponent::init(const YAML::Node &node) {
  getOptional(patrolFirst, node, "first patrol point");
  getOptional(patrolSecond, node, "second patrol point");
  getOptional(maxDistFromPatrol, node, "max distance from patrol");
  getOptional(maxViewDistance, node, "max view distance");
}

void Ground0DroidAIComponent::update(float) {
  const auto physicsComp = getExpectedCompImpl<GroundDroidPhysicsComponent>();
  if (!physicsComp->canSeePlayer()) {
    moveLeft = false;
    moveRight = false;
    return;
  }
  
  const glm::vec2 playerPos = physicsComp->getPlayerPos();
  const glm::vec2 droidPos = physicsComp->getPos();
  if (playerPos.x < droidPos.x) {
    moveLeft = true;
    moveRight = false;
  } else {
    moveLeft = false;
    moveRight = true;
  }
}

bool Ground0DroidAIComponent::shouldMoveLeft() const {
  return moveLeft;
}

bool Ground0DroidAIComponent::shouldMoveRight() const {
  return moveRight;
}
