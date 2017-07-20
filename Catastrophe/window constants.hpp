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

const bool WINDOW_RESIZABLE = true;
const Platform::Window::Desc WINDOW_DESC = {
  "Catastrophe",
  {1280, 720},
  WINDOW_RESIZABLE
};
const bool WINDOW_VSYNC = true;

const glm::ivec2 PIXELS_PER_TILE = {16, 16};
const glm::vec2 WINDOW_TILE_SIZE = {20.0f, 11.25f};
const glm::ivec2 WINDOW_PIXEL_SIZE = {
  PIXELS_PER_TILE.x * WINDOW_TILE_SIZE.x,
  PIXELS_PER_TILE.y * WINDOW_TILE_SIZE.y
};

#endif
