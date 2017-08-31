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
  : zoomVel(0.0f) {}

float CameraZoom::calcPPM(
  const CameraProps props,
  const float target,
  const float delta
) {
  return getNewPPM(
    props.pixelsPerMeter,
    Math::clamp(target, MIN_ZOOM, MAX_ZOOM),
    delta
  );
}

float CameraZoom::getNewPPM(const float ppm, const float target, const float delta) {
  return getNewPPMwithDesired(ppm, target, delta, target - ppm);
}

float CameraZoom::getNewPPMwithDesired(
  const float ppm,
  const float target,
  const float delta,
  const float desired
) {
  return applySteerOrStop(ppm, target, delta, desired, std::abs(desired));
}

float CameraZoom::applySteerOrStop(
  const float ppm,
  const float target,
  const float delta,
  const float desired,
  const float distance
) {
  if (shouldStop(distance)) {
    return applyStop(target);
  } else {
    return applySteer(ppm, scaleDesired(desired, distance), delta);
  }
}

bool CameraZoom::shouldStop(const float distance) const {
  return std::abs(zoomVel) <= ZOOM_STOP_VEL && distance <= ZOOM_STOP_DIST;
}

float CameraZoom::scaleDesired(const float desired, const float distance) const {
  return Math::sign(desired) * (
    std::min(distance, ZOOM_SLOW_DIST) / ZOOM_SLOW_DIST * MAX_ZOOM_VEL
  );
}

float CameraZoom::getSteer(const float desired) const {
  return Math::clamp(desired - zoomVel, -MAX_ZOOM_FORCE, MAX_ZOOM_FORCE);
}

float CameraZoom::applyStop(const float target) {
  zoomVel = 0.0f;
  return target;
}

float CameraZoom::applySteer(const float ppm, const float desired, const float delta) {
  zoomVel += getSteer(desired);
  return ppm + zoomVel * delta;
}
