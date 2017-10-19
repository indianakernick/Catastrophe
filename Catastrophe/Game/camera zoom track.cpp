//
//  camera zoom track.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 30/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera zoom track.hpp"

#include "nanovg.hpp"
#include "camera props.hpp"
#include "camera constants.hpp"
#include <Simpleton/Math/vectors.hpp>
#include "camera debug rendering constants.hpp"

CameraZoomTrack::CameraZoomTrack()
  : target(),
    localTarget(makeZoomTarget(DEFAULT_ZOOM_SIZE)),
    relSize(DEFAULT_ZOOM_SIZE) {}

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

void CameraZoomTrack::setRelSize(const float newSize) {
  relSize = newSize;
}

float CameraZoomTrack::calcZoomTarget(const CameraProps props) const {
  const auto targetShared = target.lock();
  if (targetShared == nullptr) {
    return props.pixelsPerMeter;
  }
  const CameraZoomTarget targetObj = *targetShared;
  
  const float targetAspect = Math::aspectRatio<float>(targetObj);
  const float windowAspect = Math::aspectRatio<float>(props.windowSize);
  
  if (targetAspect > windowAspect) {
    return (props.windowSize.x * relSize) / targetObj.x;
  } else {
    return (props.windowSize.y * relSize) / targetObj.y;
  }
}

void CameraZoomTrack::debugRender(NVGcontext *context, const CameraProps props) const {
  nvgSave(context);
  
  nvgResetTransform(context);
  nvgScale(context, props.windowSize.x, -props.windowSize.y);
  nvgTranslate(context, 0.5f, -1.0f);

  nvgBeginPath(context);
  nvgFillColor(context, CAMERA_SCALE_COLOR);
  nvgRect(context, -relSize, 0, relSize, CAMERA_SCALE_THICKNESS);
  nvgFill(context);
  
  nvgTranslate(context, 0.5f, 0.5f);
  
  nvgBeginPath(context);
  nvgFillColor(context, CAMERA_SCALE_COLOR);
  nvgRect(context, -CAMERA_SCALE_THICKNESS, relSize, CAMERA_SCALE_THICKNESS, relSize);
  nvgFill(context);
  
  nvgRestore(context);
}
