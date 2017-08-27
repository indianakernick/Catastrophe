//
//  camera zoom.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 27/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera zoom.hpp"

#include <cmath>
#include "camera constants.hpp"
#include <Simpleton/Math/scale.hpp>

CameraZoom::CameraZoom()
  : pixelsPerMeter(DEFAULT_PIXELS_PER_METER),
    zoomVel(0.0f),
    zoomTarget(pixelsPerMeter) {}

void CameraZoom::set(const float zoom) {
  assert(zoom >= MIN_ZOOM);
  assert(zoom <= MAX_ZOOM);
  
  zoomTarget = zoom;
}

float CameraZoom::get() const {
  return pixelsPerMeter;
}

void CameraZoom::animate(const float delta) {
  float desired = zoomTarget - pixelsPerMeter;
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
    pixelsPerMeter = zoomTarget;
  } else {
    zoomVel += steer;
    pixelsPerMeter += zoomVel * delta;
  }
}
