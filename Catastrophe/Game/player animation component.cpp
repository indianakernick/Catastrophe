//
//  player animation component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "player animation component.hpp"

#include "entity.hpp"
#include "vector render.hpp"
#include <Simpleton/Math/scale.hpp>
#include "player physics component.hpp"
#include <glm/gtx/matrix_transform_2d.hpp>
#include <Simpleton/Utils/safe down cast.hpp>

PlayerAnimationComponent::PlayerAnimationComponent(
  Entity *const entity,
  Sprite &&sprite,
  const Transform transform,
  const YAML::Node &
) : AnimationComponent(entity),
    sprite(std::move(sprite)),
    transform(transform),
    anim(this->sprite.animations.at("run").durationSec),
    standRun(0.125),
    footSpeed(this->sprite.animations.at("run").meta.at("foot speed")) {}

void PlayerAnimationComponent::update(const float delta) {
  const auto playerPhysics = Utils::safeDownCast<const PlayerPhysicsComponent>(getEntity().physics);
  
  const float horiVel = playerPhysics->getRelVel().x;
  switch (state) {
    case State::STANDING:
      setFrameStanding(horiVel, delta);
      break;
    case State::STARTING_TO_RUN:
      setFrameStartingToRun(horiVel, delta);
      break;
    case State::RUNNING:
      setFrameRunning(horiVel, delta);
      break;
    case State::STARTING_TO_STAND:
      setFrameStartingToStand(horiVel, delta);
      break;
    
    default:
      assert(false);
  }
  
  transform.pos = playerPhysics->getPos();
  transform.scale.x = std::abs(transform.scale.x) * calcHoriScale(horiVel);
  model = transform.getMat3();
}

const Sprite &PlayerAnimationComponent::getSprite() const {
  return sprite;
}

const Frame &PlayerAnimationComponent::getFrame() const {
  return frame;
}

glm::mat3 PlayerAnimationComponent::getModelMat() const {
  return model;
}

float PlayerAnimationComponent::calcHoriScale(const float horiVel) {
  if (horiVel < 0.0f) {
    return lastDir = -1.0f;
  } else if (horiVel > 0.0f) {
    return lastDir = 1.0f;
  } else {
    return lastDir;
  }
}

float PlayerAnimationComponent::calcAnimAdvance(const float horiVel, const float delta) const {
  return delta * Math::abs((horiVel / footSpeed) / transform.scale.x);
}

void PlayerAnimationComponent::setFrameStanding(const float horiVel, const float delta) {
  if (horiVel == 0.0f) {
    frame = ::getFrame(sprite, "stand", 0.0f);
  } else {
    state = State::STARTING_TO_RUN;
    anim.setProgressTime(0.125f);
    standRun.toBegin();
    setFrameStartingToRun(horiVel, delta);
  }
}

void PlayerAnimationComponent::setFrameStartingToRun(const float horiVel, const float delta) {
  if (horiVel == 0.0f) {
    state = State::STARTING_TO_STAND;
    setFrameStartingToStand(horiVel, delta);
  } else {
    standRun.advance(calcAnimAdvance(horiVel, delta));
    if (standRun.overflow()) {
      anim.setProgressTime(0.125f + standRun.getProgressTime() - standRun.getDuration());
      standRun.toEnd();
      state = State::RUNNING;
      return setFrameRunning(horiVel, delta);
    } else {
      Frame standingFrame = ::getFrame(sprite, "stand", 0.0f);
      lerpFrames(
        standRun.getProgress<float>(),
        standingFrame,
        ::getFrame(sprite, "run", 0.125f)
      );
      frame = standingFrame;
    }
  }
}

void PlayerAnimationComponent::setFrameRunning(const float horiVel, const float delta) {
  if (horiVel == 0.0f) {
    state = State::STARTING_TO_STAND;
    setFrameStartingToStand(horiVel, delta);
  } else {
    anim.advance(calcAnimAdvance(horiVel, delta));
    anim.repeatOnOverflow();
    frame = ::getFrame(sprite, "run", anim.getProgressTime());
  }
}

void PlayerAnimationComponent::setFrameStartingToStand(const float horiVel, const float delta) {
  //standRun is at the beginning when the player is standing and
  //            at the end       when the player is running
  if (horiVel == 0.0f) {
    standRun.advanceRev(delta);
    if (standRun.underflow()) {
      standRun.toBegin();
      state = State::STANDING;
      setFrameStanding(horiVel, delta);
    } else {
      Frame standingFrame = ::getFrame(sprite, "stand", 0.0f);
      lerpFrames(
        standRun.getProgress<float>(),
        standingFrame,
        ::getFrame(sprite, "run", anim.getProgressTime())
      );
      frame = standingFrame;
    }
  } else {
    setFrameStartingToRun(horiVel, delta);
  }
}
