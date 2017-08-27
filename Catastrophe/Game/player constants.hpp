//
//  player constants.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef player_constants_hpp
#define player_constants_hpp

constexpr float PLAYER_MOVE_FORCE = 50.0f;
constexpr float PLAYER_AIR_MOVE_FORCE = 40.0f;
constexpr float PLAYER_MAX_MOVE_SPEED = 4.0f;

constexpr float PLAYER_JUMP_IMPULSE = 2.0f;
constexpr float PLAYER_MAX_JUMP_DUR = 0.3f;
constexpr float PLAYER_LINEAR_DAMPING = 0.5f;

constexpr float PLAYER_WIDTH = 1.0f;
constexpr float PLAYER_HEIGHT = 1.0f;
constexpr float PLAYER_FOOT_HEIGHT = 0.05f;

constexpr float PLAYER_FRICTION = 0.1f;
constexpr float PLAYER_MASS = 4.0f;
constexpr float PLAYER_DENSITY = PLAYER_MASS / (PLAYER_WIDTH * PLAYER_HEIGHT);

#endif
