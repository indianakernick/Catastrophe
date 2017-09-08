//
//  camera.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 30/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera.hpp"

#include "camera visible.hpp"
#include "camera constants.hpp"

glm::mat3 Camera::toPixels() const {
  return ::toPixels(props);
}

glm::mat3 Camera::toMeters() const {
  return ::toPixels(props);
}

CameraVisible Camera::visible() const {
  return CameraVisible(props);
}

void Camera::update(const float delta) {
  const glm::vec2 motionTarget = motionTrack.calcMotionTarget(props);
  const glm::vec2 newCenter = pos.calcCenter(props, motionTarget, delta);
  
  const float zoomTarget = zoomTrack.calcZoomTarget(props);
  const float newPPM = zoom.calcPPM(props, zoomTarget, delta);
  
  const glm::vec2 newWindowSize = windowSize.get();
  
  props.center = newCenter;
  props.pixelsPerMeter = newPPM;
  props.windowSize = newWindowSize;
}

void Camera::debugRender(NVGcontext *context) {
  motionTrack.debugRender(context, props);
}
