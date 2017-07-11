//
//  constants.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_constants_hpp
#define game_constants_hpp

#include <Simpleton/Platform/window.hpp>

const Platform::Window::Desc WINDOW_DESC = {
  "Catastrophe",
  {1280, 720},
  true
};

const std::string SPRITE_SHEET_PATH = "sprites";
const glm::ivec2 PIXELS_PER_TILE = {16, 16};
const glm::ivec2 WINDOW_PIXEL_SIZE = {320, 180};

#endif
