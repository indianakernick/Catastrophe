//
//  camera zoom track.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 30/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera zoom track.hpp"

#include "camera props.hpp"
#include "camera constants.hpp"
#include <Simpleton/Math/interpolate.hpp>

CameraZoomTrack::CameraZoomTrack()
  : target(nullptr),
    localTarget(Math::middle(DEFAULT_ZOOM_MIN_SIZE, DEFAULT_ZOOM_MAX_SIZE)),
    minSize(DEFAULT_ZOOM_MIN_SIZE),
    maxSize(DEFAULT_ZOOM_MAX_SIZE) {}

void CameraZoomTrack::start(const CameraZoomTarget *newTarget) {
  target = newTarget;
}

void CameraZoomTrack::stop() {
  target = nullptr;
}

bool CameraZoomTrack::hasTarget() const {
  return target;
}

const CameraZoomTarget *CameraZoomTrack::get() const {
  return target;
}

void CameraZoomTrack::setLocal(const CameraZoomTarget newTarget) {
  localTarget = newTarget;
}

void CameraZoomTrack::startLocal() {
  target = &localTarget;
}

void CameraZoomTrack::setAndStartLocal(const CameraZoomTarget newTarget) {
  setLocal(newTarget);
  startLocal();
}

void CameraZoomTrack::setMinMaxSize(const float newSize) {
  minSize = newSize;
  maxSize = newSize;
}

void CameraZoomTrack::setMinMaxSize(const float newMinSize, const float newMaxSize) {
  if (newMinSize <= newMaxSize) {
    minSize = newMinSize;
    maxSize = newMaxSize;
  } else {
    minSize = newMaxSize;
    maxSize = newMinSize;
  }
}

float CameraZoomTrack::calcZoomTarget(const CameraProps props) const {
  if (target == nullptr) {
    return props.pixelsPerMeter;
  }
  
  const glm::length_t maxAxis = target->x < target->y ? 1 : 0;
  const float targetMaxAxis = (*target)[maxAxis];
  const float windowMaxAxis = props.windowSize[maxAxis];
  const float minSizeM = (minSize * windowMaxAxis) / props.pixelsPerMeter;
  const float maxSizeM = (maxSize * windowMaxAxis) / props.pixelsPerMeter;
  
  if (targetMaxAxis < minSizeM) {
    return (minSize * windowMaxAxis) / targetMaxAxis;
  } else if (targetMaxAxis > maxSizeM) {
    return (maxSize * windowMaxAxis) / targetMaxAxis;
  } else {
    return props.pixelsPerMeter;
  }
}
