//
//  player physics component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 3/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "player physics component.hpp"

#include <algorithm>
#include "entity.hpp"
#include "b2 glm cast.hpp"
#include "player constants.hpp"
#include <Simpleton/Math/clamp.hpp>
#include "player input component.hpp"
#include <Simpleton/Utils/safe down cast.hpp>
#include "../Libraries/Box2D/Dynamics/b2Body.h"

PlayerPhysicsComponent::PlayerPhysicsComponent(
  Entity *const entity,
  b2Body *body
) : PhysicsComponent(entity, body) {}

void PlayerPhysicsComponent::preStep(const float delta) {
  const auto playerInput = Utils::safeDownCast<const PlayerInputComponent>(getEntity().input);
  
         if (playerInput->shouldMoveLeft()) {
    moveLeft();
  } else if (playerInput->shouldMoveRight()) {
    moveRight();
  }
  if (playerInput->shouldJump()) {
    jump(delta);
  } else {
    timeTillFinishJump = 0.0f;
  }
}

void PlayerPhysicsComponent::postStep() {
  const b2Vec2 vel = body->GetLinearVelocity();
  body->SetLinearVelocity({
    Math::clampMag(vel.x, PLAYER_MAX_MOVE_SPEED),
    vel.y
  });
}

void PlayerPhysicsComponent::beginContactingGround() {
  footContactCount++;
}

void PlayerPhysicsComponent::endContactingGround() {
  footContactCount--;
}

glm::vec2 PlayerPhysicsComponent::getVel() const {
  return castToGLM(body->GetLinearVelocity());
}

bool PlayerPhysicsComponent::onGround() const {
  return footContactCount > 0;
}

void PlayerPhysicsComponent::applyMoveForce(const float moveForceDir) {
  const float moveForceMag = onGround()
                           ? PLAYER_MOVE_FORCE
                           : PLAYER_AIR_MOVE_FORCE;
  body->ApplyForceToCenter({moveForceMag * moveForceDir, 0.0f}, true);
}

void PlayerPhysicsComponent::moveLeft() {
  applyMoveForce(-1.0f);
}

void PlayerPhysicsComponent::moveRight() {
  applyMoveForce(1.0f);
}

void PlayerPhysicsComponent::jump(const float delta) {
  if (onGround() && timeTillFinishJump == 0.0f) {
    timeTillFinishJump = PLAYER_MAX_JUMP_DUR;
  }
  if (timeTillFinishJump > 0.0f) {
    body->ApplyForceToCenter({0.0f, PLAYER_JUMP_FORCE}, true);
    timeTillFinishJump = std::max(timeTillFinishJump - delta, 0.0f);
  }
}
