//
//  camera constants.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 6/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef camera_constants_hpp
#define camera_constants_hpp

#include "window constants.hpp"

const float PIXELS_PER_METER = 50.0f;
const glm::vec2 PIXELS_PER_METER_POS = {PIXELS_PER_METER, -PIXELS_PER_METER};
const glm::vec2 PIXELS_PER_METER_SIZE = {PIXELS_PER_METER, PIXELS_PER_METER};

const glm::vec2 WINDOW_METER_SIZE =
  static_cast<glm::vec2>(WINDOW_PIXEL_SIZE) / PIXELS_PER_METER_SIZE;

const glm::vec2 DEFAULT_TRACKING_BOUNDS = WINDOW_METER_SIZE / 2.0f;
constexpr float MAX_TRACKING_TIME = 1.0f;
constexpr float MAX_ZOOMING_TIME = 2.0f;
constexpr float MAX_ZOOM = 16.0f;
constexpr float MIN_ZOOM = 0.0625f;

#endif
