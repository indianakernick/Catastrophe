//
//  turret physics component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 14/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "turret physics component.hpp"

#include "systems.hpp"
#include "yaml helper.hpp"
#include "player constants.hpp"
#include <Simpleton/Math/clamp.hpp>
#include <Simpleton/Math/vectors.hpp>
#include "body physics component.hpp"

void TurretPhysicsComponent::init(b2World &, const YAML::Node &node) {
  minAngle = -INFINITY;
  maxAngle = INFINITY;
  pos = {0.0f, 0.0f};
  getOptional(pos, node, "pos");
  getOptional(minAngle, node, "min angle");
  getOptional(maxAngle, node, "max angle");
}

void TurretPhysicsComponent::preStep(float) {
  const auto comp = Systems::physics->get(PLAYER_ID).lock();
  if (!comp) {
    return;
  }
  const auto bodyComp = std::dynamic_pointer_cast<BodyPhysicsComponent>(comp);
  if (!bodyComp || !bodyComp->getBody()) {
    return;
  }
  const glm::vec2 playerPos = bodyComp->getPos();
  angle = Math::clamp(Math::angle(playerPos - pos), minAngle, maxAngle);
}

AABB TurretPhysicsComponent::getAABB() const {
  //This object doesn't exist in the physics world
  return AABB::NEG_INF;
}

glm::vec2 TurretPhysicsComponent::getPos() const {
  return pos;
}

float TurretPhysicsComponent::getAngle() const {
  return angle;
}
