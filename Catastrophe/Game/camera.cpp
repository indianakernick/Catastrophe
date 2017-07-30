//
//  camera.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 30/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera.hpp"

#include "window constants.hpp"

int sizeToPixels(const float size) {
  return size * PIXELS_PER_METER;
}

glm::ivec2 sizeToPixels(const glm::vec2 size) {
  return size * PIXELS_PER_METER;
}

glm::ivec2 sizeToPixels(const float w, const float h) {
  return sizeToPixels({w, h});
}

glm::ivec2 posToPixels(const glm::vec2 pos) {
  return {
    pos.x * PIXELS_PER_METER + WINDOW_PIXEL_SIZE.x / 2.0f,
    pos.y * -PIXELS_PER_METER + WINDOW_PIXEL_SIZE.y / 2.0f
  };
}

glm::ivec2 posToPixels(const float x, const float y) {
  return posToPixels({x, y});
}

RectPx rectToPixels(const Rect rect) {
  const glm::vec2 pos = rect.p - rect.s / 2.0f;
  return {
    posToPixels({pos.x, pos.y + rect.s.y}),
    sizeToPixels(rect.s)
  };
}

float sizeToMeters(const int size) {
  return size / PIXELS_PER_METER;
}

glm::vec2 sizeToMeters(const glm::ivec2 size) {
  return static_cast<glm::vec2>(size) / PIXELS_PER_METER;
}

glm::vec2 sizeToMeters(const int w, const int h) {
  return sizeToMeters({w, h});
}

glm::vec2 posToMeters(const glm::ivec2 pos) {
  return {
    (pos.x - WINDOW_PIXEL_SIZE.x / 2.0f) / PIXELS_PER_METER,
    (pos.y - WINDOW_PIXEL_SIZE.y / 2.0f) / -PIXELS_PER_METER
  };
}

glm::vec2 posToMeters(const int x, const int y) {
  return posToMeters({x, y});
}

Rect rectToMeters(const RectPx rect) {
  return {
    posToMeters(rect.p) + static_cast<glm::vec2>(rect.s) / 2.0f,
    sizeToMeters(rect.s)
  };
}
