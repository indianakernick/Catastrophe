//
//  simple entity controller.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "simple entity controller.hpp"

SimpleEntityController::SimpleEntityController(Entity *entity)
  : LocalEntityController(entity) {}

bool SimpleEntityController::onKeyDown(const SDL_KeyboardEvent &event) {
  switch (event.keysym.scancode) {
    case SDL_SCANCODE_UP:
      getEntity().startMoving(Math::Dir::UP);
      return true;
    case SDL_SCANCODE_RIGHT:
      getEntity().startMoving(Math::Dir::RIGHT);
      return true;
    case SDL_SCANCODE_DOWN:
      getEntity().startMoving(Math::Dir::DOWN);
      return true;
    case SDL_SCANCODE_LEFT:
      getEntity().startMoving(Math::Dir::LEFT);
      return true;
    default:
      return false;
  }
}

bool SimpleEntityController::onKeyUp(const SDL_KeyboardEvent &event) {
  switch (event.keysym.scancode) {
    case SDL_SCANCODE_UP:
    case SDL_SCANCODE_RIGHT:
    case SDL_SCANCODE_DOWN:
    case SDL_SCANCODE_LEFT:
      getEntity().stopMoving();
      return true;
    default:
      return false;
  }
}
