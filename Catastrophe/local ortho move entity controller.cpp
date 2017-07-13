//
//  local ortho move entity controller.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 13/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "local ortho move entity controller.hpp"

#include "ortho move entity.hpp"

LocalOrthoMoveEntityController::LocalOrthoMoveEntityController(
  Entity *entity,
  const Mapping mapping
) : LocalEntityController(entity),
    mapping(mapping) {}

void LocalOrthoMoveEntityController::changeMapping(const Mapping newMapping) {
  mapping = newMapping;
}

bool LocalOrthoMoveEntityController::onKeyDown(const SDL_KeyboardEvent &event) {
  OrthoMoveEntity &entity = dynamic_cast<OrthoMoveEntity &>(getEntity());
  const SDL_Scancode key = event.keysym.scancode;
         if (key == mapping.upKey) {
    entity.startMoving(Math::Dir::UP);
    return true;
  } else if (key == mapping.rightKey) {
    entity.startMoving(Math::Dir::RIGHT);
    return true;
  } else if (key == mapping.downKey) {
    entity.startMoving(Math::Dir::DOWN);
    return true;
  } else if (key == mapping.leftKey) {
    entity.startMoving(Math::Dir::LEFT);
    return true;
  } else {
    return false;
  }
}

bool LocalOrthoMoveEntityController::onKeyUp(const SDL_KeyboardEvent &event) {
  const SDL_Scancode key = event.keysym.scancode;
  if (
    key == mapping.upKey ||
    key == mapping.rightKey ||
    key == mapping.downKey ||
    key == mapping.leftKey
  ) {
    dynamic_cast<OrthoMoveEntity &>(getEntity()).stopMoving();
    return true;
  } else {
    return false;
  }
}
