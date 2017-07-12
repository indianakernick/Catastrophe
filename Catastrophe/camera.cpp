//
//  camera.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera.hpp"

#include "constants.hpp"

Camera::Camera(const glm::vec2 pos)
  : pos(pos) {}

void Camera::setPos(const glm::vec2 newPos) {
  pos = newPos;
}

glm::vec2 Camera::getSize() const {
  return {
    WINDOW_PIXEL_SIZE.x / PIXELS_PER_TILE,
    WINDOW_PIXEL_SIZE.y / PIXELS_PER_TILE
  };
}

RectPx Camera::transform(const Rect rect) const {
  return {
    static_cast<int>((rect.p.x + pos.x) * PIXELS_PER_TILE),
    static_cast<int>((rect.p.y + pos.y) * PIXELS_PER_TILE),
    static_cast<int>(rect.s.x * PIXELS_PER_TILE),
    static_cast<int>(rect.s.y * PIXELS_PER_TILE)
  };
}
