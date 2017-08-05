//
//  window constants.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 20/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef window_constants_hpp
#define window_constants_hpp

#include <Simpleton/Platform/window.hpp>

const glm::ivec2 WINDOW_PIXEL_SIZE = {1280, 720};
const bool WINDOW_RESIZABLE = false;
const Platform::Window::Desc WINDOW_DESC = {
  "Catastrophe",
  WINDOW_PIXEL_SIZE,
  WINDOW_RESIZABLE
};
const bool WINDOW_VSYNC = true;

const float PIXELS_PER_METER = 50.0f;
const glm::vec2 PIXELS_PER_METER_POS = {PIXELS_PER_METER, -PIXELS_PER_METER};
const glm::vec2 PIXELS_PER_METER_SIZE = {PIXELS_PER_METER, PIXELS_PER_METER};

const glm::vec2 WINDOW_METER_SIZE =
  static_cast<glm::vec2>(WINDOW_PIXEL_SIZE) / PIXELS_PER_METER_SIZE;

constexpr bool ENABLE_DEBUG_PHYSICS_RENDER = true;
constexpr bool ENABLE_GAME_RENDER = true;

#endif
