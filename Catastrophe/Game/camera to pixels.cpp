//
//  camera to pixels.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 27/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera to pixels.hpp"

#include "camera props.hpp"

CameraToPixels::CameraToPixels(const CameraProps props)
  : halfWindowSize(static_cast<glm::vec2>(props.windowSize) / 2.0f),
    center(props.center),
    pixelsPerMeter(props.pixelsPerMeter) {}

int CameraToPixels::size(const float s) && {
  return s * pixelsPerMeter;
}

glm::ivec2 CameraToPixels::size(const glm::vec2 s) && {
  return s * pixelsPerMeter;
}

glm::ivec2 CameraToPixels::size(const float w, const float h) && {
  return std::move(*this).size({w, h});
}

glm::ivec2 CameraToPixels::point(const glm::vec2 p) && {
  return (p - center) * std::move(*this).pixelsPerMeterPos() + halfWindowSize;
}

glm::ivec2 CameraToPixels::point(const float x, const float y) && {
  return std::move(*this).point({x, y});
}

RectPx CameraToPixels::rect(const Rect rect) && {
  const glm::ivec2 p = std::move(*this).point(rect.p);
  const glm::ivec2 s = std::move(*this).size(rect.s);
  return {{p.x, p.y - s.y}, s};
}

std::pair<glm::ivec2, int> CameraToPixels::circle(
  const glm::vec2 c,
  const float r
) && {
  return {std::move(*this).point(c), std::move(*this).size(r)};
}

std::pair<glm::ivec2, glm::ivec2> CameraToPixels::line(
  const glm::vec2 p0,
  const glm::vec2 p1
) && {
  return {std::move(*this).point(p0), std::move(*this).point(p1)};
}

glm::vec2 CameraToPixels::pixelsPerMeterPos() && {
  return {pixelsPerMeter, -pixelsPerMeter};
}
