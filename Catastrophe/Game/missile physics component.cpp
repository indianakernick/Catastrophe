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
#include "physics file.hpp"
#include "systems registry.hpp"
#include "player constants.hpp"
#include <Simpleton/Math/vectors.hpp>

MissilePhysicsComponent::MissilePhysicsComponent(
  const YAML::Node &node,
  const YAML::Node &level
) {
  Transform transform = level.as<Transform>();
  body = loadBody(getChild(node, "body").Scalar(), Systems::physics->getWorld(), transform);
  body->SetUserData(this);
  getOptional(moveSpeed, node, level, "move speed");
}

void MissilePhysicsComponent::preStep(const float delta) {
  std::shared_ptr<PhysicsComponent> comp = Systems::physics->get(PLAYER_ID).lock();
  if (!comp) {
    return;
  }
  const b2Vec2 playerPos = comp->body->GetPosition();
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
