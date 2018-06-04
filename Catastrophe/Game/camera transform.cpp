//
//  camera transform.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 13/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera transform.hpp"

#include "matrix mul.hpp"
#include "camera props.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_transform_2d.hpp>

glm::mat3 CameraTransform::toPixels() const {
  return toPixelsMat;
}

glm::mat3 CameraTransform::toMeters() const {
  return toMetersMat;
}

bool CameraTransform::visibleMeters(const AABB aabbMeters) const {
  return windowBounds.interceptsWith(aabbMeters);
}

void CameraTransform::updateMatricies(const CameraProps props) {
  static constexpr glm::mat3 I {
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}
  };
  toPixelsMat = glm::translate(
    glm::scale(
      glm::translate(
        I,
        static_cast<glm::vec2>(props.windowSize) / 2.0f
      ),
      {props.pixelsPerMeter, -props.pixelsPerMeter}
    ),
    -props.center
  );
  toMetersMat = glm::inverse(toPixelsMat);
  windowBounds.setPoint(mulPos(toMetersMat, {0.0f, 0.0f}));
  windowBounds.extendToEnclose(mulPos(toMetersMat, props.windowSize));
}
