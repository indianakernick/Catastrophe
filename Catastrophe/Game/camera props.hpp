//
//  camera props.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef camera_props_hpp
#define camera_props_hpp

#include <glm/vec2.hpp>
#include "camera constants.hpp"

struct CameraProps {
  glm::vec2 center = {0, 0};
  glm::ivec2 windowSize = DEFAULT_WINDOW_PIXEL_SIZE;
  float pixelsPerMeter = DEFAULT_PIXELS_PER_METER;
};

#endif
