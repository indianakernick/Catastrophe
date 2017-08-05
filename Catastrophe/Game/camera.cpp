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
  
  const RectPx WINDOW_RECT = RectPx(WINDOW_PIXEL_SIZE);
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

bool Camera::visible(const int x, const int y) const {
  return WINDOW_RECT.encloses({x, y});
}

bool Camera::visible(const glm::ivec2 p) const {
  return WINDOW_RECT.encloses(p);
}

bool Camera::visible(const RectPx r) const {
  return WINDOW_RECT.interceptsWith(r);
}

bool Camera::visible(const glm::ivec2 p, const int r) const {
  //https://stackoverflow.com/a/402010
  
  const glm::ivec2 HALF_WINDOW_PIXEL_SIZE = WINDOW_PIXEL_SIZE / 2;
  
  //distance between center of circle and center of rectangle (window)
  const glm::ivec2 centerDist = {
    std::abs(p.x - HALF_WINDOW_PIXEL_SIZE.x),
    std::abs(p.y - HALF_WINDOW_PIXEL_SIZE.y)
  };
  
  if (centerDist.x > HALF_WINDOW_PIXEL_SIZE.x + r) return false;
  if (centerDist.y > HALF_WINDOW_PIXEL_SIZE.y + r) return false;
  
  if (centerDist.x <= HALF_WINDOW_PIXEL_SIZE.x) return true;
  if (centerDist.y <= HALF_WINDOW_PIXEL_SIZE.y) return true;
  
  auto square = [] (const int n) {
    return n * n;
  };
  
  //squared distance between center of circle and corner
  const int cornerDist = square(centerDist.x - HALF_WINDOW_PIXEL_SIZE.x) +
                         square(centerDist.y - HALF_WINDOW_PIXEL_SIZE.y);
  return cornerDist <= square(r);
}

bool Camera::visible(glm::ivec2 p0, glm::ivec2 p1) const {
  //a few false positives are ok
  //could use SDL_IntersectRectAndLine for better accuracy
  
  if (p0.x > p1.x) {
    std::swap(p0.x, p1.x);
  }
  if (p0.y > p1.y) {
    std::swap(p0.y, p1.y);
  }
  return WINDOW_RECT.interceptsWith(RectPx(p0, p1 - p0));
}
