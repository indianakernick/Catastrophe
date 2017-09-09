//
//  camera zoom.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 27/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera zoom.hpp"

#include <cmath>
#include "camera props.hpp"
#include "camera constants.hpp"
#include <Simpleton/Math/scale.hpp>
#include <Simpleton/Math/clamp.hpp>

CameraZoom::CameraZoom()
  : vel(0.0f) {}

float CameraZoom::calcPPM(
  const CameraProps props,
  float target,
  const float delta
) {
  target = Math::clamp(target, MIN_ZOOM, MAX_ZOOM);
  const float desired = target - props.pixelsPerMeter;
  const float distance = std::abs(desired);
  
  if (shouldStop(distance)) {
    vel = 0.0f;
    return target;
  } else {
    vel += getSteer(desired, distance);
    return props.pixelsPerMeter + vel * delta;
  }
}

bool CameraZoom::shouldStop(const float distance) const {
  return std::abs(vel) <= ZOOM_STOP_VEL && distance <= ZOOM_STOP_DIST;
}

float CameraZoom::getSteer(const float desired, const float distance) const {
  const float scaledDesired = Math::sign(desired) * (
    std::min(distance, ZOOM_SLOW_DIST) / ZOOM_SLOW_DIST * MAX_ZOOM_VEL
  );
  return Math::clamp(scaledDesired - vel, -MAX_ZOOM_FORCE, MAX_ZOOM_FORCE);
}
