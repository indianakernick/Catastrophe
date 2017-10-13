//
//  camera.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 30/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera.hpp"

#include <glm/gtx/matrix_transform_2d.hpp>

namespace {
  glm::vec3 posToVec3(const glm::ivec2 v) {
    return glm::vec3(v.x, v.y, 1.0f);
  }
}

glm::mat3 Camera::toPixels() const {
  return toPixelsMat;
}

glm::mat3 Camera::toMeters() const {
  return toMetersMat;
}

bool Camera::visibleMeters(const AABB aabbMeters) const {
  return windowBounds.interceptsWith(aabbMeters);
}

void Camera::update(const float delta) {
  props.windowSize = windowSize.get();

  const glm::vec2 motionTarget = motionTrack.calcMotionTarget(props);
  const glm::vec2 newCenter = pos.calcCenter(props, motionTarget, delta);
  
  const float zoomTarget = zoomTrack.calcZoomTarget(props);
  const float newPPM = zoom.calcPPM(props, zoomTarget, delta);
  
  props.center = newCenter;
  props.pixelsPerMeter = newPPM;
  
  updateMatricies();
  windowBounds.setPoint(toMetersMat * glm::vec3(0.0f, 0.0f, 1.0f));
  windowBounds.extendToEnclose(toMetersMat * posToVec3(props.windowSize));
}

void Camera::debugRender(NVGcontext *context) {
  motionTrack.debugRender(context, props);
  zoomTrack.debugRender(context, props);
}

void Camera::updateMatricies() {
  toPixelsMat = glm::translate(
    glm::scale(
      glm::translate(
        {},
        static_cast<glm::vec2>(props.windowSize) / 2.0f
      ),
      {props.pixelsPerMeter, -props.pixelsPerMeter}
    ),
    -props.center
  );
  toMetersMat = glm::inverse(toPixelsMat);
}
