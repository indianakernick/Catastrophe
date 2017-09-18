//
//  player physics component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 3/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "player physics component.hpp"

#include <algorithm>
#include "player constants.hpp"
#include "player input commands.hpp"
#include "player physics state.hpp"
#include <Simpleton/Math/clamp.hpp>
#include "../Libraries/Box2D/Dynamics/b2Body.h"

PlayerPhysicsComponent::PlayerPhysicsComponent(b2Body *body)
  : PhysicsComponent(body) {}

void PlayerPhysicsComponent::preStep(
  PhysicsState &,
  const InputCommands &input,
  const float delta
) {
  const auto &playerInput = dynamic_cast<const PlayerInputCommands &>(input);
  handleMovement(playerInput);
  handleJump(playerInput, delta);
}

void PlayerPhysicsComponent::postStep(
  PhysicsState &physics,
  const InputCommands &
) {
  clampVel();

  auto &playerPhysics = dynamic_cast<PlayerPhysicsState &>(physics);
  playerPhysics.pos = body->GetPosition();
  playerPhysics.vel = body->GetLinearVelocity();
  playerPhysics.onGround = onGround();
}

void PlayerPhysicsComponent::beginContactingGround() {
  footContactCount++;
}

void PlayerPhysicsComponent::endContactingGround() {
  footContactCount--;
}

bool PlayerPhysicsComponent::onGround() const {
  return footContactCount > 0;
}

void PlayerPhysicsComponent::clampVel() {
  const b2Vec2 vel = body->GetLinearVelocity();
  body->SetLinearVelocity({
    Math::clampMag(vel.x, PLAYER_MAX_MOVE_SPEED),
    vel.y
  });
}

void PlayerPhysicsComponent::handleMovement(const PlayerInputCommands &input) {
  const float moveForceMag = onGround()
                           ? PLAYER_MOVE_FORCE
                           : PLAYER_AIR_MOVE_FORCE;
  const float moveForceDir = input.moveLeft * -1.0f
                           + input.moveRight * 1.0f;
  body->ApplyForceToCenter({moveForceMag * moveForceDir, 0.0f}, true);
}

void PlayerPhysicsComponent::handleJump(const PlayerInputCommands &input, const float delta) {
  if (input.jump) {
    if (onGround() && timeTillFinishJump == 0.0f) {
      timeTillFinishJump = PLAYER_MAX_JUMP_DUR;
    }
    if (timeTillFinishJump > 0.0f) {
      body->ApplyForceToCenter({0.0f, PLAYER_JUMP_FORCE}, true);
      timeTillFinishJump = std::max(timeTillFinishJump - delta, 0.0f);
    }
  } else {
    timeTillFinishJump = 0.0f;
  }
}
