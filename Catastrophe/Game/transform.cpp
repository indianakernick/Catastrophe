//
//  transform.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "transform.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_transform_2d.hpp>

Transform::Transform()
  : Transform({0.0f, 0.0f}) {}

Transform::Transform(const glm::vec2 pos)
  : Transform(pos, {1.0f, 1.0f}) {}

Transform::Transform(
  const glm::vec2 pos,
  const glm::vec2 scale,
  const float rotation
) : pos(pos),
    scale(scale),
    rotation(rotation) {}

namespace {
  constexpr glm::mat3 I {
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}
  };
}

glm::mat2 Transform::getMat2() const {
  return glm::scale(glm::rotate(I, rotation), scale);
}

glm::mat3 Transform::getMat3() const {
  return glm::scale(glm::rotate(glm::translate(I, pos), rotation), scale);
}
