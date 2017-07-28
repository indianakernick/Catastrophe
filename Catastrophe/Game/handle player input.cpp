//
//  handle player input.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 20/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "handle player input.hpp"

#include <cassert>
#include "player.hpp"
#include <SDL2/SDL_events.h>
#include "input constants.hpp"

void handleKeyDown(Player &player, const SDL_KeyboardEvent keyEvent) {
  assert(keyEvent.type == SDL_KEYDOWN);
  
  if (keyEvent.repeat) {
    return;
  }
  
  const SDL_Scancode key = keyEvent.keysym.scancode;
  if (key == LEFT_KEY) {
    player.startMovingLeft();
  }
  if (key == RIGHT_KEY) {
    player.startMovingRight();
  }
  if (key == JUMP_KEY) {
    player.startJumping();
  }
}

void handleKeyUp(Player &player, const SDL_KeyboardEvent keyEvent) {
  assert(keyEvent.type == SDL_KEYUP);
  
  const SDL_Scancode key = keyEvent.keysym.scancode;
  if (key == LEFT_KEY) {
    player.stopMovingLeft();
  }
  if (key == RIGHT_KEY) {
    player.stopMovingRight();
  }
  if (key == JUMP_KEY) {
    player.stopJumping();
  }
}

void handlePlayerInput(Player &player, const SDL_Event e) {
  if (e.type == SDL_KEYDOWN) {
    handleKeyDown(player, e.key);
  } else if (e.type == SDL_KEYUP) {
    handleKeyUp(player, e.key);
  }
}
