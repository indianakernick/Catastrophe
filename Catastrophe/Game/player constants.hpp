//
//  player constants.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef player_constants_hpp
#define player_constants_hpp

#include <SDL2/SDL_scancode.h>

constexpr SDL_Scancode PLAYER_LEFT_KEY  = SDL_SCANCODE_A;
constexpr SDL_Scancode PLAYER_RIGHT_KEY = SDL_SCANCODE_D;
constexpr SDL_Scancode PLAYER_JUMP_KEY  = SDL_SCANCODE_SPACE;

constexpr float PLAYER_MOVE_FORCE = 60.0f;
constexpr float PLAYER_MAX_MOVE_SPEED = 4.0f;
constexpr float PLAYER_JUMP_FORCE = 120.0f;
constexpr float PLAYER_MAX_JUMP_DUR = 1.0f;

constexpr float PLAYER_WIDTH = 1.0f;
constexpr float PLAYER_HEIGHT = 1.0f;
constexpr float PLAYER_MASS = 60.0f;
constexpr float PLAYER_DENSITY = PLAYER_MASS / (PLAYER_WIDTH * PLAYER_HEIGHT);

#endif
