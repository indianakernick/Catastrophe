//
//  player animation component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "player animation component.hpp"

#include "b2 glm cast.hpp"
#include "vector render.hpp"
#include "player physics state.hpp"
#include <Simpleton/Math/scale.hpp>
#include "vector rendering state.hpp"
#include <glm/gtx/matrix_transform_2d.hpp>

PlayerAnimationComponent::PlayerAnimationComponent(
  Entity *const entity,
  const Sprite &sprite
) : AnimationComponent(entity),
    sprite(sprite),
    anim(sprite.animations.at("run").durationSec),
    standRun(0.125),
    footSpeed(sprite.animations.at("run").meta.at("foot speed")) {}

void PlayerAnimationComponent::update(
  RenderingState &rendering,
  const PhysicsState &physics,
  const float delta
) {
  VectorRenderingState &vectorRender = dynamic_cast<VectorRenderingState &>(rendering);
  const PlayerPhysicsState &playerPhysics = dynamic_cast<const PlayerPhysicsState &>(physics);
  
  vectorRender.shapes = sprite.shapes;
  
  const float horiVel = playerPhysics.vel.x;
  switch (state) {
    case State::STANDING:
      vectorRender.frame = getFrameStanding(horiVel, delta);
      break;
    case State::STARTING_TO_RUN:
      vectorRender.frame = getFrameStartingToRun(horiVel, delta);
      break;
    case State::RUNNING:
      vectorRender.frame = getFrameRunning(horiVel, delta);
      break;
    case State::STARTING_TO_STAND:
      vectorRender.frame = getFrameStartingToStand(horiVel, delta);
      break;
    
    default:
      assert(false);
  }
  
  vectorRender.modelMat = glm::translate({}, castToGLM(physics.pos));
  vectorRender.modelMat = glm::scale(vectorRender.modelMat, {calcHoriScale(horiVel), 1.0f});
}

float PlayerAnimationComponent::calcHoriScale(const float horiVel) {
  if (horiVel < 0.0f) {
    lastDir = -1.0f;
    return lastDir;
  } else if (horiVel > 0.0f) {
    lastDir = 1.0f;
    return lastDir;
  } else {
    return lastDir;
  }
}

float PlayerAnimationComponent::calcAnimAdvance(const float horiVel, const float delta) const {
  return delta * Math::abs(horiVel / footSpeed);
}

Frame PlayerAnimationComponent::getFrameStanding(const float horiVel, const float delta) {
  if (horiVel == 0.0f) {
    return getFrame(sprite, "stand", 0.0f);
  } else {
    state = State::STARTING_TO_RUN;
    anim.setProgressTime(0.125f);
    standRun.toBegin();
    return getFrameStartingToRun(horiVel, delta);
  }
}

Frame PlayerAnimationComponent::getFrameStartingToRun(const float horiVel, const float delta) {
  if (horiVel == 0.0f) {
    state = State::STARTING_TO_STAND;
    return getFrameStartingToStand(horiVel, delta);
  } else {
    standRun.advance(calcAnimAdvance(horiVel, delta));
    if (standRun.overflow()) {
      anim.setProgressTime(0.125f + standRun.getProgressTime() - standRun.getDuration());
      standRun.toEnd();
      state = State::RUNNING;
      return getFrameRunning(horiVel, delta);
    } else {
      Frame standingFrame = getFrame(sprite, "stand", 0.0f);
      lerpFrames(
        standRun.getProgress<float>(),
        standingFrame,
        getFrame(sprite, "run", 0.125f)
      );
      return standingFrame;
    }
  }
}

Frame PlayerAnimationComponent::getFrameRunning(const float horiVel, const float delta) {
  if (horiVel == 0.0f) {
    state = State::STARTING_TO_STAND;
    return getFrameStartingToStand(horiVel, delta);
  } else {
    anim.advance(calcAnimAdvance(horiVel, delta));
    anim.repeatOnOverflow();
    return getFrame(sprite, "run", anim.getProgressTime());
  }
}

Frame PlayerAnimationComponent::getFrameStartingToStand(const float horiVel, const float delta) {
  //standRun is at the beginning when the player is standing and
  //            at the end       when the player is running
  if (horiVel == 0.0f) {
    standRun.advanceRev(delta);
    if (standRun.underflow()) {
      standRun.toBegin();
      state = State::STANDING;
      return getFrameStanding(horiVel, delta);
    } else {
      Frame standingFrame = getFrame(sprite, "stand", 0.0f);
      lerpFrames(
        standRun.getProgress<float>(),
        standingFrame,
        getFrame(sprite, "run", anim.getProgressTime())
      );
      return standingFrame;
    }
  } else {
    return getFrameStartingToRun(horiVel, delta);
  }
}
