//
//  player animation component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "player animation component.hpp"

#include "entity.hpp"
#include "yaml helper.hpp"
#include <Simpleton/Math/scale.hpp>
#include "player physics component.hpp"
#include <Simpleton/Utils/safe down cast.hpp>

void PlayerAnimationComponent::init(const YAML::Node &node) {
  transform.scale = getChild(node, "scale").as<glm::vec2>();
  runningAnim.setDuration(getChild(node, "run duration").as<float>());
  standRunAnim.setDuration(getChild(node, "foot time").as<float>());
  groundJumpAnim.setDuration(getChild(node, "jump time").as<float>());
  footSpeed = getChild(node, "foot speed").as<float>();
}

void PlayerAnimationComponent::update(const float delta) {
  const auto playerPhysics = Utils::safeDownCast<const PlayerPhysicsComponent>(
    getEntity().get<PhysicsComponent>()
  );
  
  const float horiVel = playerPhysics->getRelVel().x;
  const bool onGround = playerPhysics->onGround();
  
  handleMove(horiVel, onGround, delta);
  handleJump(onGround, delta);
  
  transform.pos = playerPhysics->getPos();
  transform.scale.x = std::abs(transform.scale.x) * calcHoriScale(horiVel);
  model = transform.getMat3();
}

float PlayerAnimationComponent::getProgress() const {
  return 0.0f;
}

glm::mat3 PlayerAnimationComponent::getModelMat() const {
  return model;
}

bool PlayerAnimationComponent::getRightLeg() const {
  return rightLeg;
}

float PlayerAnimationComponent::getGroundJumpProg() const {
  return groundJumpAnim.getProgress<float>();
}

float PlayerAnimationComponent::getStandRunProg() const {
  return standRunAnim.getProgress<float>();
}

float PlayerAnimationComponent::getRunningProg() const {
  return runningAnim.getProgressTime();
}

float PlayerAnimationComponent::calcHoriScale(const float horiVel) {
  if (std::abs(horiVel) < 0.01f) {
    return lastDir;
  } else if (horiVel < 0.0f) {
    return lastDir = -1.0f;
  } else {
    return lastDir = 1.0f;
  }
}

float PlayerAnimationComponent::calcRunAdvance(const float horiVel, const float delta) const {
  return delta * Math::abs((horiVel / footSpeed) / transform.scale.x);
}

void PlayerAnimationComponent::handleMove(
  const float horiVel,
  const bool onGround,
  const float delta
) {
  switch (moveState) {
    case MoveState::STANDING:
      return standing(horiVel, onGround, delta);
    case MoveState::START_RUN:
      return startRun(horiVel, onGround, delta);
    case MoveState::RUNNING:
      return running(horiVel, onGround, delta);
    case MoveState::START_STAND:
      return startStand(horiVel, onGround, delta);
    
    default:
      assert(false);
  }
}

void PlayerAnimationComponent::handleJump(
  const bool onGround,
  const float delta
) {
  switch (jumpState) {
    case JumpState::GROUNDED:
      return grounded(onGround, delta);
    case JumpState::START_JUMP:
      return startJump(onGround, delta);
    case JumpState::JUMPING:
      return jumping(onGround, delta);
    case JumpState::START_GROUND:
      return startGround(onGround, delta);
    
    default:
      assert(false);
  }
}

void PlayerAnimationComponent::standing(
  const float horiVel,
  const bool onGround,
  const float delta
) {
  if (horiVel != 0.0f) {
    moveState = MoveState::START_RUN;
    if (rightLeg) {
      runningAnim.setProgressTime(0.5f);
    } else {
      runningAnim.setProgressTime(0.0f);
    }
    startRun(horiVel, onGround, delta);
  }
}

void PlayerAnimationComponent::startRun(
  const float horiVel,
  const bool onGround,
  const float delta
) {
  if (horiVel == 0.0f) {
    moveState = MoveState::START_STAND;
    startStand(horiVel, onGround, delta);
  } else {
    standRunAnim.advance(calcRunAdvance(horiVel, delta));
    if (standRunAnim.overflow()) {
      runningAnim.advance(standRunAnim.overflowTime());
      standRunAnim.toEnd();
      moveState = MoveState::RUNNING;
      running(horiVel, onGround, delta);
    }
  }
}

void PlayerAnimationComponent::running(
  const float horiVel,
  const bool onGround,
  const float delta
) {
  if (horiVel == 0.0f) {
    moveState = MoveState::START_STAND;
    startStand(horiVel, onGround, delta);
  } else if (onGround) {
    runningAnim.advance(calcRunAdvance(horiVel, delta));
    runningAnim.repeatOnOverflow();
    rightLeg = runningAnim.getProgressTime() >= 0.5f;
  }
}

void PlayerAnimationComponent::startStand(
  const float horiVel,
  const bool onGround,
  const float delta
) {
  //standRun is at the beginning when the player is standing and
  //            at the end       when the player is running
  if (horiVel == 0.0f) {
    standRunAnim.advanceRev(delta);
    if (standRunAnim.stopOnBegin()) {
      moveState = MoveState::STANDING;
      standing(horiVel, onGround, delta);
    }
  } else {
    moveState = MoveState::START_RUN;
    startRun(horiVel, onGround, delta);
  }
}

void PlayerAnimationComponent::grounded(
  const bool onGround,
  const float delta
) {
  if (!onGround) {
    jumpState = JumpState::START_JUMP;
    startJump(onGround, delta);
  }
}

void PlayerAnimationComponent::startJump(
  const bool onGround,
  const float delta
) {
  if (onGround) {
    jumpState = JumpState::START_GROUND;
    startGround(onGround, delta);
  } else {
    groundJumpAnim.advance(delta);
    if (groundJumpAnim.stopOnEnd()) {
      jumpState = JumpState::JUMPING;
      jumping(onGround, delta);
    }
  }
}

void PlayerAnimationComponent::jumping(
  const bool onGround,
  const float delta
) {
  if (onGround) {
    jumpState = JumpState::START_GROUND;
    startGround(onGround, delta);
  }
}

void PlayerAnimationComponent::startGround(
  const bool onGround,
  const float delta
) {
  if (onGround) {
    groundJumpAnim.advanceRev(delta);
    if (groundJumpAnim.stopOnBegin()) {
      jumpState = JumpState::GROUNDED;
      grounded(onGround, delta);
    }
  } else {
    jumpState = JumpState::START_JUMP;
    startJump(onGround, delta);
  }
}
