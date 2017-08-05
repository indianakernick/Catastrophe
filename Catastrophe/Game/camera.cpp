//
//  camera.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 30/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera.hpp"

#include "window constants.hpp"

namespace {
  const glm::vec2 HALF_WINDOW_PIXEL_SIZE =
    static_cast<glm::vec2>(WINDOW_PIXEL_SIZE) / 2.0f;
}

Camera::Camera()
  : center(WINDOW_METER_SIZE / 2.0f) {}

int Camera::sizeToPixels(const float s) const {
  return s * PIXELS_PER_METER;
}

glm::ivec2 Camera::sizeToPixels(const glm::vec2 s) const {
  return s * PIXELS_PER_METER;
}

glm::ivec2 Camera::sizeToPixels(const float w, const float h) const {
  return sizeToPixels({w, h});
}

glm::ivec2 Camera::posToPixels(const glm::vec2 p) const {
  return (p - center) * PIXELS_PER_METER_POS + HALF_WINDOW_PIXEL_SIZE;
}

glm::ivec2 Camera::posToPixels(const float x, const float y) const {
  return posToPixels({x, y});
}

float Camera::sizeToMeters(const int s) const {
  return static_cast<float>(s) / PIXELS_PER_METER;
}

glm::vec2 Camera::sizeToMeters(const glm::ivec2 s) const {
  return static_cast<glm::vec2>(s) / PIXELS_PER_METER;
}

glm::vec2 Camera::sizeToMeters(const int w, const int h) const {
  return sizeToMeters({w, h});
}

glm::vec2 Camera::posToMeters(const glm::ivec2 p) const {
  return
    (static_cast<glm::vec2>(p) - HALF_WINDOW_PIXEL_SIZE) /
    PIXELS_PER_METER_POS + center
  ;
}

glm::vec2 Camera::posToMeters(const int x, const int y) const {
  return posToMeters({x, y});
}
