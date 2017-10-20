//
//  camera.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 30/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera.hpp"

void Camera::update(const glm::ivec2 windowSize, const float delta) {
  props.windowSize = windowSize;

  const glm::vec2 motionTarget = motionTrack.calcMotionTarget(props);
  const glm::vec2 newCenter = pos.calcCenter(props, motionTarget, delta);
  
  const float zoomTarget = zoomTrack.calcZoomTarget(props);
  const float newPPM = zoom.calcPPM(props, zoomTarget, delta);
  
  props.center = newCenter;
  props.pixelsPerMeter = newPPM;
  
  transform.updateMatricies(props);
}

CameraProps Camera::getProps() const {
  return props;
}
