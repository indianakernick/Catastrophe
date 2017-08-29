//
//  camera to meters.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 27/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera to meters.hpp"

#include "camera props.hpp"

CameraToMeters::CameraToMeters(const CameraProps props)
  : halfWindowSize(static_cast<glm::vec2>(props.windowSize) / 2.0f),
    center(props.center),
    pixelsPerMeter(props.pixelsPerMeter) {}

float CameraToMeters::size(const int s) && {
  return static_cast<float>(s) / pixelsPerMeter;
}

glm::vec2 CameraToMeters::size(const glm::ivec2 s) && {
  return static_cast<glm::vec2>(s) / pixelsPerMeter;
}

glm::vec2 CameraToMeters::size(const int w, const int h) && {
  return std::move(*this).size({w, h});
}

glm::vec2 CameraToMeters::point(const glm::ivec2 p) && {
  return
    (static_cast<glm::vec2>(p) - halfWindowSize) /
    std::move(*this).pixelsPerMeterPos() + center
  ;
}

glm::vec2 CameraToMeters::point(const int x, const int y) && {
  return std::move(*this).point({x, y});
}

Rect CameraToMeters::rect(const RectPx rect) && {
  const glm::vec2 p = std::move(*this).point(rect.p);
  const glm::vec2 s = std::move(*this).size(rect.s);
  return {{p.x, p.y + s.y}, s};
}

std::pair<glm::vec2, float> CameraToMeters::circle(
  const glm::ivec2 c,
  const int r
) && {
  return {std::move(*this).point(c), std::move(*this).size(r)};
}

std::pair<glm::vec2, glm::vec2> CameraToMeters::line(
  const glm::ivec2 p0,
  const glm::ivec2 p1
) && {
  return {std::move(*this).point(p0), std::move(*this).point(p1)};
}

glm::vec2 CameraToMeters::pixelsPerMeterPos() && {
  return {pixelsPerMeter, -pixelsPerMeter};
}
