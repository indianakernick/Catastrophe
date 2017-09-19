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
#include "player input commands.hpp"

PlayerInputComponent::PlayerInputComponent(Entity *const entity)
  : InputComponent(entity) {}

bool PlayerInputComponent::handleEvent(InputCommands &commands, const SDL_Event event) {
  if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
    return handleKey(commands, event.key.keysym.scancode, true);
  } else if (event.type == SDL_KEYUP) {
    return handleKey(commands, event.key.keysym.scancode, false);
  } else {
    return false;
  }
}

bool PlayerInputComponent::handleKey(
  InputCommands &commands,
  const SDL_Scancode key,
  const bool down
) {
  auto &playerCommands = dynamic_cast<PlayerInputCommands &>(commands);
  
  switch (key) {
    case PLAYER_LEFT_KEY:
      leftButton = down;
      break;
    case PLAYER_RIGHT_KEY:
      rightButton = down;
      break;
    case PLAYER_JUMP_KEY:
      playerCommands.jump = down;
      break;
      
    default:
      return false;
  }

  playerCommands.moveLeft  = leftButton  && !rightButton;
  playerCommands.moveRight = rightButton && !leftButton;
  
  return true;
}
