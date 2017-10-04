//
//  component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "component.hpp"

#include <cassert>

Component::~Component() {}

void Component::setEntity(Entity *const newEntity) {
  assert(entity == nullptr);
  assert(newEntity != nullptr);
  entity = newEntity;
}

Entity &Component::getEntity() const {
  return *entity;
}
