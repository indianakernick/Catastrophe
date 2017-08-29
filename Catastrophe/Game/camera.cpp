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
#include "camera to pixels.hpp"
#include "camera to meters.hpp"

CameraToPixels Camera::toPixels() const {
  return CameraToPixels(props);
}

CameraToMeters Camera::toMeters() const {
  return CameraToMeters(props);
}

CameraVisible Camera::visible() const {
  return CameraVisible(props);
}

void Camera::update(const float delta) {
  const glm::vec2 motionTarget = track.calcMotionTarget(props);
  const glm::vec2 newCenter = pos.calcCenter(props, motionTarget, delta);
  
  const float zoomTarget = props.pixelsPerMeter;
  const float newPPM = zoom.calcPPM(props, zoomTarget, delta);
  
  const glm::vec2 newWindowSize = windowSize.get();
  
  props.center = newCenter;
  props.pixelsPerMeter = newPPM;
  props.windowSize = newWindowSize;
}

void Camera::debugRender() {
  if (renderer != nullptr) {
    track.debugRender(props, *renderer);
  }
}

void Camera::attachRenderer(RenderingContext &newRenderer) {
  renderer = &newRenderer;
}

void Camera::detachRenderer() {
  renderer = nullptr;
}
