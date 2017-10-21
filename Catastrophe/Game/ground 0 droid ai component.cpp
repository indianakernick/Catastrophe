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
  if (patrolSecond < patrolFirst) {
    std::swap(patrolFirst, patrolSecond);
  }
}

void Ground0DroidAIComponent::update(float) {
  const auto physicsComp = getExpectedCompImpl<GroundDroidPhysicsComponent>();
  const glm::vec2 playerPos = physicsComp->getPlayerPos();
  const glm::vec2 droidPos = physicsComp->getPos();
  const float dist = std::max(
    patrolFirst - droidPos.x,
    droidPos.x - patrolSecond
  );
  
  if (!physicsComp->canSeePlayer() || dist > maxDistFromPatrol) {
    patrol(droidPos.x);
  } else {
    chase(droidPos.x, playerPos.x);
  }
}

bool Ground0DroidAIComponent::shouldMoveLeft() const {
  return !moveRight;
}

bool Ground0DroidAIComponent::shouldMoveRight() const {
  return moveRight;
}

bool Ground0DroidAIComponent::shouldMoveFast() const {
  return chasing;
}

void Ground0DroidAIComponent::patrol(const float droidX) {
  chasing = false;
  if (toSecond && droidX > patrolSecond) {
    toSecond = false;
  } else if (!toSecond && droidX < patrolFirst) {
    toSecond = true;
  }
  moveRight = toSecond;
}

void Ground0DroidAIComponent::chase(const float droidX, const float playerX) {
  chasing = true;
  moveRight = playerX > droidX;
}
