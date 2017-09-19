//
//  camera zoom track.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 30/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera zoom track.hpp"

#include <nanovg/nanovg.h>
#include "camera props.hpp"
#include "camera constants.hpp"
#include <Simpleton/Math/interpolate.hpp>
#include "camera debug render constants.hpp"

CameraZoomTrack::CameraZoomTrack()
  : target(),
    localTarget(makeZoomTarget(
      Math::middle(DEFAULT_ZOOM_MIN_SIZE, DEFAULT_ZOOM_MAX_SIZE)
    )),
    minSize(DEFAULT_ZOOM_MIN_SIZE),
    maxSize(DEFAULT_ZOOM_MAX_SIZE) {}

void CameraZoomTrack::start(const CameraZoomTargetCPtr newTarget) {
  target = newTarget;
}

void CameraZoomTrack::stop() {
  target.reset();
}

void CameraZoomTrack::setLocal(const CameraZoomTarget newTarget) {
  *localTarget = newTarget;
}

void CameraZoomTrack::startLocal() {
  target = localTarget;
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
  const auto targetShared = target.lock();
  if (targetShared == nullptr) {
    return props.pixelsPerMeter;
  }
  const CameraZoomTarget targetObj = *targetShared;
  
  const glm::length_t maxAxis = targetObj.x < targetObj.y ? 1 : 0;
  const float targetMaxAxis = targetObj[maxAxis];
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

void CameraZoomTrack::debugRender(NVGcontext *context, const CameraProps props) const {
  nvgSave(context);
    nvgResetTransform(context);
    nvgScale(context, props.windowSize.x, -props.windowSize.y);
    nvgTranslate(context, 0.5f, -1.0f);
  
    nvgBeginPath(context);
    nvgStrokeColor(context, CAMERA_SCALE_COLOR);
    nvgStrokeWidth(context, CAMERA_SCALE_THICKNESS);
    nvgLineCap(context, NVG_BUTT);
  
    nvgMoveTo(context, -maxSize / 2.0f, CAMERA_SCALE_THICKNESS * 0.5f);
    nvgLineTo(context, maxSize / 2.0f, CAMERA_SCALE_THICKNESS * 0.5f);
  
    nvgMoveTo(context, -minSize / 2.0f, CAMERA_SCALE_THICKNESS * 1.5f);
    nvgLineTo(context, minSize / 2.0f, CAMERA_SCALE_THICKNESS * 1.5f);
  
    nvgStroke(context);
  nvgRestore(context);
}
