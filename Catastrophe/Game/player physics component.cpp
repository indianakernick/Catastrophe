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
#include "yaml helper.hpp"
#include "b2 glm cast.hpp"
#include "limit velocity.hpp"
#include "player constants.hpp"
#include <Simpleton/Math/clamp.hpp>
#include "player input component.hpp"
#include "../Libraries/Box2D/Dynamics/b2Body.h"

void PlayerPhysicsComponent::init(b2World &world, const YAML::Node &node) {
  BodyPhysicsComponent::init(world, node);
  moveForce = getChild(node, "move force").as<float>();
  airMoveForce = getChild(node, "air move force").as<float>();
  maxMoveSpeed = getChild(node, "max move speed").as<float>();
  jumpForce = getChild(node, "jump force").as<float>();
  maxJumpDur = getChild(node, "max jump duration").as<float>();
}

void PlayerPhysicsComponent::preStep(const float delta) {
  const auto playerInput = getExpectedCompImpl<const PlayerInputComponent>();
  
         if (playerInput->shouldMoveLeft()) {
    applyMoveForce(-1.0f);
  } else if (playerInput->shouldMoveRight()) {
    applyMoveForce(1.0f);
  }
  if (playerInput->shouldJump()) {
    jump(delta);
  } else {
    timeTillFinishJump = 0.0f;
  }
}

void PlayerPhysicsComponent::postStep() {
  body->SetLinearVelocity(
    limitVelX(body->GetLinearVelocity(), groundContact.getGroundVel(), maxMoveSpeed)
  );
}

void PlayerPhysicsComponent::beginContactingGround(b2Body *groundBody) {
  groundContact.beginContactingGround(groundBody);
}

void PlayerPhysicsComponent::endContactingGround(b2Body *groundBody) {
  groundContact.endContactingGround(groundBody);
}

glm::vec2 PlayerPhysicsComponent::getRelVel() const {
  return castToGLM(body->GetLinearVelocity() - groundContact.getGroundVel());
}

bool PlayerPhysicsComponent::onGround() const {
  return groundContact.onGround();
}

void PlayerPhysicsComponent::applyMoveForce(const float moveForceDir) {
  const float moveForceMag = onGround() ? moveForce : airMoveForce;
  body->ApplyForceToCenter({moveForceMag * moveForceDir, 0.0f}, true);
}

void PlayerPhysicsComponent::jump(const float delta) {
  if (onGround() && timeTillFinishJump == 0.0f) {
    timeTillFinishJump = maxJumpDur;
  }
  if (timeTillFinishJump > 0.0f) {
    body->ApplyForceToCenter({0.0f, jumpForce}, true);
    timeTillFinishJump = std::max(timeTillFinishJump - delta, 0.0f);
  }
}
