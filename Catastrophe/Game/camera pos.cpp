//
//  camera pos.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 27/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera pos.hpp"

#include "camera props.hpp"
#include <glm/gtx/norm.hpp>
#include "camera constants.hpp"
#include <Simpleton/Math/scale.hpp>

CameraPos::CameraPos()
  : vel(0.0f, 0.0f),
    lastTarget(0.0f, 0.0f) {}

glm::vec2 CameraPos::calcCenter(
  const CameraProps props,
  const glm::vec2 target,
  const float delta
) {
  const glm::vec2 desired = target - props.center;
  const float distance = glm::length(desired);
  if (shouldStop(target, distance)) {
    vel = {0.0f, 0.0f};
    lastTarget = target;
    return target;
  } else {
    vel += getSteer(desired, distance);
    lastTarget = props.center + vel * delta;
    return lastTarget;
  }
}

bool CameraPos::shouldStop(const glm::vec2 target, const float distance) const {
  return
    glm::length2(vel) <= MOVE_STOP_VEL * MOVE_STOP_VEL &&
    distance <= MOVE_STOP_DIST &&
    target == lastTarget
  ;
}

glm::vec2 CameraPos::getSteer(const glm::vec2 desired, const float distance) const {
  const glm::vec2 scaledDesired = glm::sign(desired) * (
    std::min(distance, MOVE_SLOW_DIST) / MOVE_SLOW_DIST * MAX_MOVE_VEL
  );
  return glm::clamp(scaledDesired - vel, -MAX_MOVE_FORCE, MAX_MOVE_FORCE);
}
