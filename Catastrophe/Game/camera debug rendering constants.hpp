//
//  camera debug rendering constants.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 17/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef camera_debug_rendering_constants_hpp
#define camera_debug_rendering_constants_hpp

#include "nanovg.hpp"

const NVGcolor CAMERA_TARGET_COLOR = nvgRGBAf(1.0f, 1.0f, 0.0f, 0.5f);
const NVGcolor CAMERA_TRACK_COLOR = nvgRGBAf(0.0f, 1.0f, 0.0f, 0.5f);
const NVGcolor CAMERA_SCALE_COLOR = nvgRGBAf(1.0f, 1.0f, 1.0f, 0.5f);
constexpr float CAMERA_SCALE_THICKNESS = 0.01f;

#endif
