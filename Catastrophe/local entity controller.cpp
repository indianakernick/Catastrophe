//
//  local entity controller.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "local entity controller.hpp"

LocalEntityController::LocalEntityController(Entity *entity)
  : EntityController(entity) {}

LocalEntityController::~LocalEntityController() {}

bool LocalEntityController::onKeyDown(const SDL_KeyboardEvent &) {
  return false;
}

bool LocalEntityController::onKeyUp(const SDL_KeyboardEvent &) {
  return false;
}

bool LocalEntityController::onMouseDown(const SDL_MouseButtonEvent &) {
  return false;
}

bool LocalEntityController::onMouseUp(const SDL_MouseButtonEvent &) {
  return false;
}

bool LocalEntityController::onMouseMove(const SDL_MouseMotionEvent &) {
  return false;
}
