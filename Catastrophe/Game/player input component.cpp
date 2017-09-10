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

bool PlayerInputComponent::handleEvent(InputCommands &commands, const SDL_Event event) {
  if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
    return handleKeyDown(commands, event.key.keysym.scancode);
  } else if (event.type == SDL_KEYUP) {
    return handleKeyUp(commands, event.key.keysym.scancode);
  } else {
    return false;
  }
}

bool PlayerInputComponent::handleKeyDown(InputCommands &commands, const SDL_Scancode key) {
  PlayerInputCommands &playerCommands = dynamic_cast<PlayerInputCommands &>(commands);
  
  switch (key) {
    case PLAYER_LEFT_KEY:
      leftButton = true;
      break;
    case PLAYER_RIGHT_KEY:
      rightButton = true;
      break;
    case PLAYER_JUMP_KEY:
      playerCommands.jump = true;
      break;
      
    default:
      return false;
  }
  
  if (leftButton && rightButton) {
    playerCommands.moveLeft = false;
    playerCommands.moveRight = false;
  } else {
    playerCommands.moveLeft = leftButton;
    playerCommands.moveRight = rightButton;
  }
  
  return true;
}

bool PlayerInputComponent::handleKeyUp(InputCommands &commands, const SDL_Scancode key) {
  PlayerInputCommands &playerCommands = dynamic_cast<PlayerInputCommands &>(commands);
  
  switch (key) {
    case PLAYER_LEFT_KEY:
      leftButton = false;
      break;
    case PLAYER_RIGHT_KEY:
      rightButton = false;
      break;
    case PLAYER_JUMP_KEY:
      playerCommands.jump = false;
      break;
      
    default:
      return false;
  }
  
  if (leftButton && rightButton) {
    playerCommands.moveLeft = false;
    playerCommands.moveRight = false;
  } else {
    playerCommands.moveLeft = leftButton;
    playerCommands.moveRight = rightButton;
  }
  
  return true;
}
