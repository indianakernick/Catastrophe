//
//  matrix mul.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 3/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "matrix mul.hpp"

#include <Simpleton/Math/scale.hpp>

glm::vec2 mulPoint(const glm::mat3 &mat, const glm::vec2 point) {
  return mat * glm::vec3(point.x, point.y, 1.0f);
}

glm::vec2 mulSize(const glm::mat3 &mat, const glm::vec2 size) {
  return glm::abs(mat * glm::vec3(size.x, size.y, 0.0f));
}

float mulSize(const glm::mat3 &mat, const float size) {
  return Math::abs(size * mat[0][0]);
}

RectPx mulRect(const glm::mat3 &mat, const Rect rect) {
  const glm::ivec2 p = mulPoint(mat, rect.p);
  const glm::ivec2 s = mulSize(mat, rect.s);
  return {{p.x, p.y - s.y}, s};
}

Rect mulRectPx(const glm::mat3 &mat, const RectPx rect) {
  const glm::vec2 p = mulPoint(mat, rect.p);
  const glm::vec2 s = mulSize(mat, rect.s);
  return {{p.x, p.y + s.y}, s};
}

std::pair<glm::vec2, float> mulCircle(
  const glm::mat3 &mat,
  const glm::vec2 center,
  const float radius
) {
  return {mulPoint(mat, center), mulSize(mat, radius)};
}

std::pair<glm::vec2, glm::vec2> mulLine(
  const glm::mat3 &mat,
  const glm::vec2 p0,
  const glm::vec2 p1
) {
  return {mulPoint(mat, p0), mulPoint(mat, p1)};
}
