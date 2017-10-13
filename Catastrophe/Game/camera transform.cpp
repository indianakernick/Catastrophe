//
//  camera transform.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 13/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera transform.hpp"

#include "camera props.hpp"
#include <glm/gtx/matrix_transform_2d.hpp>

namespace {
  glm::vec3 posToVec3(const glm::ivec2 v) {
    return glm::vec3(v.x, v.y, 1.0f);
  }
}

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
  toPixelsMat = glm::translate(
    glm::scale(
      glm::translate(
        {},
        static_cast<glm::vec2>(props.windowSize) / 2.0f
      ),
      {props.pixelsPerMeter, -props.pixelsPerMeter}
    ),
    -props.center
  );
  toMetersMat = glm::inverse(toPixelsMat);
  windowBounds.setPoint(toMetersMat * glm::vec3(0.0f, 0.0f, 1.0f));
  windowBounds.extendToEnclose(toMetersMat * posToVec3(props.windowSize));
}
