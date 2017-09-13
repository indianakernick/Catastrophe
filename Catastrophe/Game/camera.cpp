//
//  camera.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 30/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera.hpp"

#include <glm/gtx/matrix_transform_2d.hpp>

glm::mat3 Camera::toPixels() const {
  return glm::translate(
    glm::scale(
      glm::translate(
        {},
        static_cast<glm::vec2>(props.windowSize) / 2.0f
      ),
      {props.pixelsPerMeter, -props.pixelsPerMeter}
    ),
    -props.center
  );
}

glm::mat3 Camera::toMeters() const {
  return glm::inverse(toPixels());
}

bool Camera::visibleMeters(const Rect aabbMeters) const {
  const glm::ivec2 posPixels = toPixels() * glm::vec3(aabbMeters.p.x, aabbMeters.p.y, 1.0f);
  const glm::ivec2 sizePixels = aabbMeters.s * props.pixelsPerMeter;
  const RectPx aabbPixels = {{posPixels.x, posPixels.y - sizePixels.y}, sizePixels};
  return RectPx(props.windowSize).interceptsWith(aabbPixels);
}

void Camera::update(const float delta) {
  props.windowSize = windowSize.get();

  const glm::vec2 motionTarget = motionTrack.calcMotionTarget(props);
  const glm::vec2 newCenter = pos.calcCenter(props, motionTarget, delta);
  
  const float zoomTarget = zoomTrack.calcZoomTarget(props);
  const float newPPM = zoom.calcPPM(props, zoomTarget, delta);
  
  props.center = newCenter;
  props.pixelsPerMeter = newPPM;
}

void Camera::debugRender(NVGcontext *context) {
  motionTrack.debugRender(context, props);
}
