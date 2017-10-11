//
//  missile physics component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "missile physics component.hpp"

#include "yaml helper.hpp"
#include "b2 glm cast.hpp"
#include "systems registry.hpp"
#include "player constants.hpp"
#include <Simpleton/Math/vectors.hpp>

void MissilePhysicsComponent::init(b2World &world, const YAML::Node &node) {
  BodyPhysicsComponent::init(world, node);
  getOptional(moveSpeed, node, "move speed");
}

void MissilePhysicsComponent::preStep(float) {
  const auto comp = Systems::physics->get(PLAYER_ID).lock();
  if (!comp) {
    return;
  }
  const auto bodyComp = std::dynamic_pointer_cast<BodyPhysicsComponent>(comp);
  if (!bodyComp || !bodyComp->getBody()) {
    return;
  }
  const b2Vec2 playerPos = bodyComp->getBody()->GetPosition();
  const b2Vec2 missilePos = body->GetPosition();
  const b2Vec2 missileToPlayer = playerPos - missilePos;
  const float newAngle = Math::angle(missileToPlayer);
  body->SetTransform(missilePos, newAngle);
  body->SetLinearVelocity(castToB2(Math::angleMag(newAngle, moveSpeed)));
}

void MissilePhysicsComponent::postStep() {
  if (contacted) {
    //@TODO destroy self
  }
}

void MissilePhysicsComponent::beginContact() {
  contacted = true;
}
