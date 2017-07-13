//
//  simple entity controller.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "simple entity controller.hpp"

#include "ortho move entity.hpp"

SimpleEntityController::SimpleEntityController(Entity *entity)
  : LocalEntityController(entity) {}

bool SimpleEntityController::onKeyDown(const SDL_KeyboardEvent &event) {
  OrthoMoveEntity &entity = dynamic_cast<OrthoMoveEntity &>(getEntity());
  switch (event.keysym.scancode) {
    case SDL_SCANCODE_UP:
      entity.startMoving(Math::Dir::UP);
      return true;
    case SDL_SCANCODE_RIGHT:
      entity.startMoving(Math::Dir::RIGHT);
      return true;
    case SDL_SCANCODE_DOWN:
      entity.startMoving(Math::Dir::DOWN);
      return true;
    case SDL_SCANCODE_LEFT:
      entity.startMoving(Math::Dir::LEFT);
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
      dynamic_cast<OrthoMoveEntity &>(getEntity()).stopMoving();
      return true;
    default:
      return false;
  }
}
