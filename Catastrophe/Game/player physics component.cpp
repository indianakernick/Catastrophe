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
#include "physics file.hpp"
#include "systems registry.hpp"
#include "player constants.hpp"
#include <Simpleton/Math/clamp.hpp>
#include "player input component.hpp"
#include <Simpleton/Utils/safe down cast.hpp>
#include "../Libraries/Box2D/Dynamics/b2Body.h"

PlayerPhysicsComponent::PlayerPhysicsComponent(
  const YAML::Node &node,
  const YAML::Node &level
) {
  Transform transform;
  transform.pos = getChild(level, "pos").as<glm::vec2>();
  transform.scale = getChild(node, "scale").as<glm::vec2>();
  body = loadBody(getChild(node, "body").Scalar(), Systems::physics->getWorld(), transform);
  body->SetUserData(this);
  
  moveForce = getChild(node, "move force").as<float>();
  airMoveForce = getChild(node, "air move force").as<float>();
  maxMoveSpeed = getChild(node, "max move speed").as<float>();
  jumpForce = getChild(node, "jump force").as<float>();
  maxJumpDur = getChild(node, "max jump duration").as<float>();
}

void PlayerPhysicsComponent::preStep(const float delta) {
  const auto playerInput = Utils::safeDownCast<const PlayerInputComponent>(getEntity().input);
  
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
  const b2Vec2 groundVel = groundBodies.empty()
                         ? b2Vec2(0.0f, 0.0f)
                         : groundBodies.front()->GetLinearVelocity();
  const b2Vec2 relVel = body->GetLinearVelocity() - groundVel;
  body->SetLinearVelocity({
    Math::clampMag(relVel.x, maxMoveSpeed) + groundVel.x,
    relVel.y + groundVel.y
  });
}

void PlayerPhysicsComponent::beginContactingGround(b2Body *groundBody) {
  groundBodies.push_front(groundBody);
}

void PlayerPhysicsComponent::endContactingGround(b2Body *groundBody) {
  groundBodies.remove(groundBody);
}

glm::vec2 PlayerPhysicsComponent::getRelVel() const {
  if (groundBodies.empty()) {
    return castToGLM(body->GetLinearVelocity());
  } else {
    const b2Vec2 groundVel = groundBodies.front()->GetLinearVelocity();
    return castToGLM(body->GetLinearVelocity() - groundVel);
  }
}

bool PlayerPhysicsComponent::onGround() const {
  return !groundBodies.empty();
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
