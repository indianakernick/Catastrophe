//
//  missile physics component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "missile physics component.hpp"

#include "systems.hpp"
#include "yaml helper.hpp"
#include "b2 glm cast.hpp"
#include "player constants.hpp"
#include <Simpleton/Math/vectors.hpp>
#include "destroyable spawn component.hpp"

void MissilePhysicsComponent::init(b2World &world, const YAML::Node &node) {
  BodyPhysicsComponent::init(world, node);
  getOptional(moveForce, node, "move force");
  getOptional(turnTorque, node, "turn torque");
}

namespace {
  float relativeAngle(float abs) {
    while (abs > b2_pi) {
      abs -= b2_pi;
    }
    while (abs < -b2_pi) {
      abs += b2_pi;
    }
    return abs;
  }
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
  b2Vec2 missileToPlayer = bodyComp->getBody()->GetPosition() - body->GetPosition();
  missileToPlayer.Normalize();
  missileToPlayer *= TOP_SPEED;
  const float targetAngle = Math::angle(missileToPlayer - body->GetLinearVelocity());
  body->SetTransform(body->GetPosition(), targetAngle);
  const float force = moveForce * (1.0f - std::abs(relativeAngle(targetAngle - Math::angle(missileToPlayer))) / b2_pi);
  
  const glm::vec2 forceVec = Math::angleMag(targetAngle, force);
  body->ApplyForceToCenter(castToB2(forceVec), true);
}

void MissilePhysicsComponent::postStep() {
  if (contacted) {
    const auto spawnComp = getExpectedCompImpl<DestroyableSpawnComponent>();
    spawnComp->kill();
  }
}

void MissilePhysicsComponent::beginContact() {
  contacted = true;
}
