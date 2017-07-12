//
//  entity controller.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "entity controller.hpp"

#include <cassert>

EntityController::EntityController(Entity *entity)
  : entity(entity) {
  assert(entity);
}

EntityController::~EntityController() {}

void EntityController::setEntity(Entity *newEntity) {
  assert(newEntity);
  entity = newEntity;
}
