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

constexpr bool WINDOW_RESIZABLE = true;
constexpr bool WINDOW_VSYNC = true;
constexpr bool WINDOW_OPENGL = true;

const Platform::Window::Desc WINDOW_DESC = {
  "The Legend of the Pink Pentagon",
  DEFAULT_WINDOW_PIXEL_SIZE,
  WINDOW_RESIZABLE,
  WINDOW_OPENGL
};

#endif
