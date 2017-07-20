//
//  handle player input.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 20/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "handle player input.hpp"

Math::Dir keyToDir(const SDL_Scancode key) {
  switch (key) {
    case SDL_SCANCODE_UP:
      std::cout << "UP";
      return Math::Dir::UP;
    case SDL_SCANCODE_RIGHT:
      std::cout << "RIGHT";
      return Math::Dir::RIGHT;
    case SDL_SCANCODE_DOWN:
      std::cout << "DOWN";
      return Math::Dir::DOWN;
    case SDL_SCANCODE_LEFT:
      std::cout << "LEFT";
      return Math::Dir::LEFT;
    default:
      return Math::Dir::NONE;
  }
}

void handleKeyDown(Player &player, const SDL_KeyboardEvent keyEvent) {
  assert(keyEvent.type == SDL_KEYDOWN);
  
  if (keyEvent.repeat) {
    return;
  }
  
  const Math::Dir moveDir = keyToDir(keyEvent.keysym.scancode);
  if (moveDir != Math::Dir::NONE) {
    std::cout << " press\n";
    player.startMoving(moveDir);
    std::cout << "---------------------\n";
    player.printState();
    std::cout << "---------------------\n";
  }
}

void handleKeyUp(Player &player, const SDL_KeyboardEvent keyEvent) {
  assert(keyEvent.type == SDL_KEYUP);
  
  const Math::Dir moveDir = keyToDir(keyEvent.keysym.scancode);
  if (moveDir != Math::Dir::NONE) {
    std::cout << " release\n";
    player.stopMoving(moveDir);
    std::cout << "---------------------\n";
    player.printState();
    std::cout << "---------------------\n";
  }
}

void handlePlayerInput(Player &player, const SDL_Event e) {
  if (e.type == SDL_KEYDOWN) {
    handleKeyDown(player, e.key);
  } else if (e.type == SDL_KEYUP) {
    handleKeyUp(player, e.key);
  } else if (e.type == SDL_MOUSEBUTTONDOWN) {
    std::cout << "\n\n";
  }
}
