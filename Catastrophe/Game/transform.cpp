//
//  transform.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "transform.hpp"

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

glm::mat2 Transform::getMat2() const {
  return glm::scale(glm::rotate(glm::mat3(), rotation), scale);
}

glm::mat3 Transform::getMat3() const {
  return glm::scale(glm::rotate(glm::translate({}, pos), rotation), scale);
}
