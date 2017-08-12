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

const float DEFAULT_PIXELS_PER_METER = 50.0f;
const glm::vec2 DEFAULT_TRACKING_BOUNDS = glm::vec2(1.0f, 1.0f) / 2.0f;
constexpr float MAX_ZOOM = 128.0f;
constexpr float MIN_ZOOM = 16.0f;

constexpr float MAX_ZOOM_VEL = 64.0f;
constexpr float MAX_ZOOM_FORCE = 16.0f;
//distance from zoom target to start slowing down
constexpr float ZOOM_SLOW_DIST = 32.0f;
//distance from zoom target stop
constexpr float ZOOM_STOP_DIST = 0.05f;


#endif
