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
