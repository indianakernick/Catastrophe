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

constexpr float DEFAULT_PIXELS_PER_METER = 64.0f;

const glm::vec2 DEFAULT_TRACKING_BOUNDS_CENTER = {0.0f, 0.0f};
const glm::vec2 DEFAULT_TRACKING_BOUNDS_SIZE = glm::vec2(1.0f, 1.0f) / 3.0f;

constexpr float MIN_ZOOM = 8.0f;
constexpr float MAX_ZOOM = 256.0f;

constexpr float DEFAULT_ZOOM_SIZE = 1.0f / 32.0f;

constexpr float MAX_ZOOM_VEL = 16.0f;
constexpr float MAX_ZOOM_FORCE = 8.0f;
//distance from zoom target to start slowing down
constexpr float ZOOM_SLOW_DIST = 16.0f;
//velocity of zoom to stop at
constexpr float ZOOM_STOP_VEL = 0.2f;
constexpr float ZOOM_STOP_DIST = 0.1f;

constexpr float MAX_MOVE_VEL = 32.0f;
constexpr float MAX_MOVE_FORCE = 16.0f;
constexpr float MOVE_SLOW_DIST = 16.0f;
constexpr float MOVE_STOP_VEL = 0.05f;
constexpr float MOVE_STOP_DIST = 0.025f;

#endif
