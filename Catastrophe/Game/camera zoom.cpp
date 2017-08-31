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
  float zoomTarget,
  const float delta
) {
  zoomTarget = Math::clamp(zoomTarget, MIN_ZOOM, MAX_ZOOM);

  const float oldPPM = props.pixelsPerMeter;
  float newPPM;

  float desired = zoomTarget - oldPPM;
  const float distance = std::abs(desired);
  if (distance != 0.0f) {
    desired /= distance;
  }
  
  if (distance <= ZOOM_SLOW_DIST) {
    desired *= Math::scale(distance, 0.0f, ZOOM_SLOW_DIST, 0.0f, MAX_ZOOM_VEL);
  } else {
    desired *= MAX_ZOOM_VEL;
  }
  
  float steer = desired - zoomVel;
  if (std::abs(steer) > MAX_ZOOM_FORCE) {
    steer = Math::sign(steer) * MAX_ZOOM_FORCE;
  }
 
  if (std::abs(zoomVel) <= ZOOM_STOP_VEL && distance <= ZOOM_STOP_DIST) {
    zoomVel = 0.0f;
    newPPM = zoomTarget;
  } else {
    zoomVel += steer;
    newPPM = oldPPM + zoomVel * delta;
  }
  
  return newPPM;
}
