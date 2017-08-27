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
#include "camera scale tracking bounds.hpp"

CameraToPixels Camera::toPixels() const {
  return CameraToPixels(windowSize.half(), pos.get(), zoom.get());
}

CameraToMeters Camera::toMeters() const {
  return CameraToMeters(windowSize.half(), pos.get(), zoom.get());
}

CameraVisible Camera::visible() const {
  return CameraVisible(windowSize.get());
}

void Camera::update(const float delta) {
  track.setTargetPos(pos, scaleTrack());
  pos.animate(delta);
  zoom.animate(delta);
}

void Camera::debugRender() {
  if (renderer != nullptr) {
    track.debugRender(*renderer, scaleTrack());
  }
}

void Camera::attachRenderer(RenderingContext &newRenderer) {
  renderer = &newRenderer;
}

void Camera::detachRenderer() {
  renderer = nullptr;
}

CameraScaleTrackingBounds Camera::scaleTrack() const {
  return CameraScaleTrackingBounds(windowSize.get(), pos.get(), zoom.get());
}
