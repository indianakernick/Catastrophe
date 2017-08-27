//
//  camera scale tracking bounds.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 27/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera scale tracking bounds.hpp"

CameraScaleTrackingBounds::CameraScaleTrackingBounds(
  const glm::vec2 windowSize,
  const glm::vec2 center,
  const float pixelsPerMeter
) : windowSize(windowSize),
    center(center),
    pixelsPerMeter(pixelsPerMeter) {}

glm::vec2 CameraScaleTrackingBounds::centerToMeters(const glm::vec2 c) const {
  return center + toMeters(c);
}

glm::vec2 CameraScaleTrackingBounds::sizeToMeters(const glm::vec2 s) const {
  return toMeters(s);
}

glm::vec2 CameraScaleTrackingBounds::toMeters(const glm::vec2 v) const {
  return (v * windowSize) / pixelsPerMeter;
}
