//
//  ground droid physics component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "ground droid physics component.hpp"

#include "systems.hpp"
#include "yaml helper.hpp"
#include "object types.hpp"
#include "player constants.hpp"
#include <Simpleton/Math/clamp.hpp>
#include "ground 0 droid ai component.hpp"
#include "../Libraries/Box2D/Dynamics/b2Body.h"

namespace {
  class RayCastCallback : public b2RayCastCallback {
  public:
    RayCastCallback() = default;
    
    float32 ReportFixture(
      b2Fixture *const fixture,
      const b2Vec2 &,
      const b2Vec2 &,
      float32
    ) {
      if (fixture->GetUserData() != getUserData<Symbol::PlayerBody>()) {
        hitPlayer = false;
        return 0.0f;
      } else {
        return 1.0f;
      }
    }
    
    bool hasHitPlayer() const {
      return hitPlayer;
    }
    
  private:
    bool hitPlayer = true;
  };
}

void GroundDroidPhysicsComponent::init(b2World &world, const YAML::Node &node) {
  BodyPhysicsComponent::init(world, node);
  getOptional(moveForce, node, "move force");
  getOptional(maxMoveSpeed, node, "max move speed");
}

void GroundDroidPhysicsComponent::preStep(float) {
  const auto aiComp = getExpectedCompImpl<Ground0DroidAIComponent>();
  if (aiComp->shouldMoveLeft()) {
    applyMoveForce(-1.0f);
  } else if (aiComp->shouldMoveRight()) {
    applyMoveForce(1.0f);
  }
}

void GroundDroidPhysicsComponent::postStep() {
  const auto bodyComp = getExpectedCompImpl<BodyPhysicsComponent>();
  const auto physicsComp = Systems::physics.get(PLAYER_ID).lock();
  if (!physicsComp) {
    return;
  }
  const auto playerComp = std::dynamic_pointer_cast<BodyPhysicsComponent>(physicsComp);
  if (!playerComp || !playerComp->getBody()) {
    return;
  }
  playerPos = playerComp->getPos();
  
  b2World *const world = Systems::physics.getWorld();
  RayCastCallback raycast;
  world->RayCast(
    &raycast,
    bodyComp->getBody()->GetPosition(),
    playerComp->getBody()->GetPosition()
  );
  seePlayer = raycast.hasHitPlayer();
  
  const b2Vec2 vel = body->GetLinearVelocity();
  body->SetLinearVelocity({
    Math::clampMag(vel.x, maxMoveSpeed),
    vel.y
  });
}

float GroundDroidPhysicsComponent::getVelX() const {
  //I don't think there's any point in getting the velocity relative to the
  //ground like PlayerPhysicsComponent does.
  return body->GetLinearVelocity().x;
}

bool GroundDroidPhysicsComponent::canSeePlayer() const {
  return seePlayer;
}

glm::vec2 GroundDroidPhysicsComponent::getPlayerPos() const {
  return playerPos;
}

void GroundDroidPhysicsComponent::applyMoveForce(const float moveDir) {
  body->ApplyForceToCenter({moveForce * moveDir, 0.0f}, true);
}
