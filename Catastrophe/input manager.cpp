//
//  input manager.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 11/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "input manager.hpp"

#include "input commands.hpp"

InputCommand::Ptr InputManager::handleInput(const SDL_Event event) {
  if (event.type == SDL_KEYDOWN) {
    switch (event.key.keysym.scancode) {
      case SDL_SCANCODE_UP:
        return std::make_shared<MoveCommand>(Math::Dir::UP);
      case SDL_SCANCODE_RIGHT:
        return std::make_shared<MoveCommand>(Math::Dir::RIGHT);
      case SDL_SCANCODE_DOWN:
        return std::make_shared<MoveCommand>(Math::Dir::DOWN);
      case SDL_SCANCODE_LEFT:
        return std::make_shared<MoveCommand>(Math::Dir::LEFT);
      default: ;
    }
  }
  
  return nullptr;
}
