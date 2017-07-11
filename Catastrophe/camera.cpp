//
//  camera.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera.hpp"

#include <glm/gtx/matrix_transform_2d.hpp>

void Camera::setPos(const glm::vec2 newPos) {
  pos = newPos;
}

SDL_Rect Camera::transform(const glm::vec2 spritePos, const glm::vec2 spriteSize) const {
  return {
    static_cast<int>((spritePos.x + pos.x) * PIXELS_PER_TILE),
    static_cast<int>((spritePos.y + pos.y) * PIXELS_PER_TILE),
    static_cast<int>(spriteSize.x * PIXELS_PER_TILE),
    static_cast<int>(spriteSize.y * PIXELS_PER_TILE)
  };
}
