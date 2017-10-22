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
#include <Simpleton/Math/scale.hpp>
#include "ground droid ai component.hpp"
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
      if (fixture->IsSensor()) {
        return -1.0f;
      }
      if (fixture->GetUserData() != getUserData<Symbol::PlayerBody>()) {
        hitPlayer = false;
        return 0.0f;
      } else {
        return -1.0f;
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
  getOptional(maxMoveForce, node, "max move force");
  getOptional(maxViewDistance, node, "max view distance");
  getOptional(slowMoveSpeed, node, "slow move speed");
  getOptional(fastMoveSpeed, node, "fast move speed");
}

void GroundDroidPhysicsComponent::preStep(const float delta) {
  const auto aiComp = getExpectedCompImpl<GroundDroidAIComponent>();
  facingDir = aiComp->getMoveDir();
  const float dir = calcMoveDir(facingDir);
  const float speed = calcMoveSpeed(aiComp->getMoveSpeed());
  const float targetVel = dir * speed;
  const float actualVel = body->GetLinearVelocity().x;
  //The force needed to accelerate the body to the target velocity in one frame
  const float force = (targetVel - actualVel) / delta * body->GetMass();
  applyMoveForce(force);
}

void GroundDroidPhysicsComponent::postStep() {
  lookForPlayer();
}

bool GroundDroidPhysicsComponent::canSeePlayer() const {
  return seePlayer;
}

glm::vec2 GroundDroidPhysicsComponent::getPlayerPos() const {
  return castToGLM(playerPos);
}

glm::vec2 GroundDroidPhysicsComponent::getRelVel() const {
  return castToGLM(body->GetLinearVelocity() - groundContact.getGroundVel());
}

bool GroundDroidPhysicsComponent::onGround() const {
  return groundContact.onGround();
}

float GroundDroidPhysicsComponent::getDir() const {
  return calcMoveDir(facingDir);
}

void GroundDroidPhysicsComponent::beginContactingGround(b2Body *const body) {
  groundContact.beginContactingGround(body);
}

void GroundDroidPhysicsComponent::endContactingGround(b2Body *const body) {
  groundContact.endContactingGround(body);
}

float GroundDroidPhysicsComponent::calcMoveDir(const MoveDir dir) const {
  return dir == MoveDir::RIGHT ? 1.0f : -1.0f;
}

float GroundDroidPhysicsComponent::calcMoveSpeed(const MoveSpeed speed) const {
  if (speed == MoveSpeed::STOP) {
    return 0.0f;
  } else if (speed == MoveSpeed::SLOW) {
    return slowMoveSpeed;
  } else {
    return fastMoveSpeed;
  }
}

void GroundDroidPhysicsComponent::applyMoveForce(const float force) {
  if (onGround()) {
    body->ApplyForceToCenter({Math::clampMag(force, maxMoveForce), 0.0f}, true);
  }
}

auto GroundDroidPhysicsComponent::getPlayer() const {
  const auto physicsComp = Systems::physics.get(PLAYER_ID).lock();
  if (!physicsComp) {
    throw std::runtime_error("Expected player to have a physics component");
  }
  const auto playerComp = std::dynamic_pointer_cast<BodyPhysicsComponent>(physicsComp);
  if (!playerComp || !playerComp->getBody()) {
    throw std::runtime_error("Expected player to have an initialized physics body");
  }
  return playerComp;
}

void GroundDroidPhysicsComponent::lookForPlayer() {
  b2World *const world = Systems::physics.getWorld();
  const auto bodyComp = getExpectedCompImpl<BodyPhysicsComponent>();
  const auto playerComp = getPlayer();
  const b2Vec2 droidPos = bodyComp->getBody()->GetPosition();
  playerPos = playerComp->getBody()->GetPosition();
  const float playerDroidDist = (playerPos - droidPos).LengthSquared();
  
  if (Math::sign(playerPos.x - droidPos.x) != Math::sign(getDir())) {
    seePlayer = false;
  } else if (playerDroidDist > maxViewDistance*maxViewDistance) {
    seePlayer = false;
  } else {
    RayCastCallback raycast;
    world->RayCast(
      &raycast,
      droidPos,
      playerPos
    );
    seePlayer = raycast.hasHitPlayer();
  }
}
