//
//  component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "component.hpp"

#include <cassert>

Component::Component(Entity *const entity)
  : entity(entity) {
  assert(entity);
}

Component::~Component() {}

Entity &Component::getEntity() const {
  return *entity;
}
