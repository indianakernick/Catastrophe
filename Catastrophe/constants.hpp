//
//  constants.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_constants_hpp
#define game_constants_hpp

#include <SDL2/SDL_scancode.h>
#include <Simpleton/Platform/window.hpp>

const Platform::Window::Desc WINDOW_DESC = {
  "Catastrophe",
  {1280, 720},
  true
};
const bool VSYNC = true;

const std::string SPRITE_SHEET_PATH = "sprites";
const glm::ivec2 PIXELS_PER_TILE = {16, 16};
const glm::vec2 WINDOW_TILE_SIZE = {20.0f, 11.25f};
const glm::ivec2 WINDOW_PIXEL_SIZE = {
  PIXELS_PER_TILE.x * WINDOW_TILE_SIZE.x,
  PIXELS_PER_TILE.y * WINDOW_TILE_SIZE.y
};

const float PLAYER_MOVE_SPEED = 4.0f;

constexpr SDL_Scancode UP_KEY    = SDL_SCANCODE_W;
constexpr SDL_Scancode RIGHT_KEY = SDL_SCANCODE_D;
constexpr SDL_Scancode DOWN_KEY  = SDL_SCANCODE_S;
constexpr SDL_Scancode LEFT_KEY  = SDL_SCANCODE_A;

#endif
