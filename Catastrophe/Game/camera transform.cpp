//
//  camera transform.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 3/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera transform.hpp"

#include "camera props.hpp"
#include <glm/gtx/matrix_transform_2d.hpp>

glm::mat3 toPixels(const CameraProps props) {
  return glm::translate(
    glm::scale(
      glm::translate(
        {},
        static_cast<glm::vec2>(props.windowSize) / 2.0f
      ),
      {props.pixelsPerMeter, -props.pixelsPerMeter}
    ),
    -props.center
  );
}

glm::mat3 toMeters(const CameraProps props) {
  return glm::inverse(toPixels(props));
}

glm::vec2 mulPoint(const glm::mat3 &mat, const glm::vec2 point) {
  return mat * glm::vec3(point.x, point.y, 1.0f);
}

glm::vec2 mulSize(const glm::mat3 &mat, const glm::vec2 size) {
  return size * mat[0][0];
}

float mulSize(const glm::mat3 &mat, const float size) {
  return size * mat[0][0];
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
