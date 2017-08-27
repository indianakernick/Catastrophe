//
//  camera to meters.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 27/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera to meters.hpp"

CameraToMeters::CameraToMeters(
  const glm::vec2 halfWindowSize,
  const glm::vec2 center,
  const float pixelsPerMeter
) : halfWindowSize(halfWindowSize),
    center(center),
    pixelsPerMeter(pixelsPerMeter) {}

float CameraToMeters::size(const int s) const {
  return static_cast<float>(s) / pixelsPerMeter;
}

glm::vec2 CameraToMeters::size(const glm::ivec2 s) const {
  return static_cast<glm::vec2>(s) / pixelsPerMeter;
}

glm::vec2 CameraToMeters::size(const int w, const int h) const {
  return size({w, h});
}

glm::vec2 CameraToMeters::pos(const glm::ivec2 p) const {
  return
    (static_cast<glm::vec2>(p) - halfWindowSize) /
    pixelsPerMeterPos() + center
  ;
}

glm::vec2 CameraToMeters::pos(const int x, const int y) const {
  return pos({x, y});
}

Rect CameraToMeters::rect(const RectPx rect) const {
  const glm::vec2 p = pos(rect.p);
  const glm::vec2 s = size(rect.s);
  return {{p.x, p.y + s.y}, s};
}

glm::vec2 CameraToMeters::pixelsPerMeterPos() const {
  return {pixelsPerMeter, -pixelsPerMeter};
}
