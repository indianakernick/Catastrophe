//
//  camera pos.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 27/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera pos.hpp"

#include <glm/gtx/norm.hpp>
#include "camera constants.hpp"
#include <Simpleton/Math/scale.hpp>

CameraPos::CameraPos()
  : center(0.0f, 0.0f),
    motionVel(0.0f, 0.0f),
    motionTarget(0.0f, 0.0f),
    lastMotionTarget(0.0f, 0.0f) {}

void CameraPos::set(const glm::vec2 pos) {
  lastMotionTarget = pos;
  motionTarget = pos;
}

void CameraPos::setMoving(const glm::vec2 pos) {
  lastMotionTarget = motionTarget;
  motionTarget = pos;
}

glm::vec2 CameraPos::get() const {
  return center;
}

void CameraPos::animate(const float delta) {
  glm::vec2 desired = motionTarget - center;
  const float distance = glm::length(desired);
  if (distance != 0.0f) {
    desired /= distance;
  }
  
  if (distance <= MOVE_SLOW_DIST) {
    desired *= Math::scale(distance, 0.0f, MOVE_SLOW_DIST, 0.0f, MAX_MOVE_VEL);
  } else {
    desired *= MAX_MOVE_VEL;
  }
  
  glm::vec2 steer = desired - motionVel;
  if (glm::length2(steer) > MAX_MOVE_FORCE * MAX_MOVE_FORCE) {
    steer = glm::normalize(steer);
    steer *= MAX_MOVE_FORCE;
  }
  
  if (
    glm::length2(motionVel) <= MOVE_STOP_VEL * MOVE_STOP_VEL &&
    distance <= MOVE_STOP_DIST &&
    motionTarget == lastMotionTarget
  ) {
    motionVel = {0.0f, 0.0f};
    center = motionTarget;
  } else {
    motionVel += steer;
    center += motionVel * delta;
  }
}
