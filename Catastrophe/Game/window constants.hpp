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

const glm::ivec2 DEFAULT_WINDOW_PIXEL_SIZE = {1280, 720};
const bool WINDOW_RESIZABLE = true;
const Platform::Window::Desc WINDOW_DESC = {
  "Catastrophe",
  DEFAULT_WINDOW_PIXEL_SIZE,
  WINDOW_RESIZABLE
};
const bool WINDOW_VSYNC = true;

constexpr bool ENABLE_DEBUG_PHYSICS_RENDER = false;
constexpr bool ENABLE_DEBUG_CAMERA_RENDER = true;
constexpr bool ENABLE_GAME_RENDER = true;
constexpr bool ENABLE_DEBUG_INPUT_LOG = false;

constexpr unsigned MAX_INPUT_EVENTS_PER_FRAME = 64;

#endif
