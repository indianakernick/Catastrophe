//
//  camera to pixels.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 27/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera to pixels.hpp"

CameraToPixels::CameraToPixels(
  const glm::vec2 halfWindowSize,
  const glm::vec2 center,
  const float pixelsPerMeter
) : halfWindowSize(halfWindowSize),
    center(center),
    pixelsPerMeter(pixelsPerMeter) {}

int CameraToPixels::size(const float s) const {
  return s * pixelsPerMeter;
}

glm::ivec2 CameraToPixels::size(const glm::vec2 s) const {
  return s * pixelsPerMeter;
}

glm::ivec2 CameraToPixels::size(const float w, const float h) const {
  return size({w, h});
}

glm::ivec2 CameraToPixels::pos(const glm::vec2 p) const {
  return (p - center) * pixelsPerMeterPos() + halfWindowSize;
}

glm::ivec2 CameraToPixels::pos(const float x, const float y) const {
  return pos({x, y});
}

RectPx CameraToPixels::rect(const Rect rect) const {
  const glm::ivec2 p = pos(rect.p);
  const glm::ivec2 s = size(rect.s);
  return {{p.x, p.y - s.y}, s};
}

glm::vec2 CameraToPixels::pixelsPerMeterPos() const {
  return {pixelsPerMeter, -pixelsPerMeter};
}
