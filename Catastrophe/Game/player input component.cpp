//
//  player input component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "player input component.hpp"

#include <SDL2/SDL_events.h>
#include "input constants.hpp"

PlayerInputComponent::PlayerInputComponent(const YAML::Node &, const YAML::Node &) {}

bool PlayerInputComponent::handleEvent(const SDL_Event event) {
  if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
    return handleKey(event.key.keysym.scancode, true);
  } else if (event.type == SDL_KEYUP) {
    return handleKey(event.key.keysym.scancode, false);
  } else {
    return false;
  }
}

bool PlayerInputComponent::shouldMoveLeft() const {
  return leftButton && !rightButton;
}

bool PlayerInputComponent::shouldMoveRight() const {
  return rightButton && !leftButton;
}

bool PlayerInputComponent::shouldJump() const {
  return jumpButton;
}

bool PlayerInputComponent::handleKey(const SDL_Scancode key, const bool down) {
  switch (key) {
    case PLAYER_LEFT_KEY:
      leftButton = down;
      return true;
    case PLAYER_RIGHT_KEY:
      rightButton = down;
      return true;
    case PLAYER_JUMP_KEY:
      jumpButton = down;
      return true;
      
    default:
      return false;
  }
}
