//
//  physics system.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 23/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "physics system.hpp"

void PhysicsSystem::add(
  const EntityID id,
  std::shared_ptr<PhysicalObject> object
) {
  assert(object);
  objects.add(id, object);
}

void PhysicsSystem::rem(const EntityID id) {
  objects.rem(id);
}

void PhysicsSystem::update(const float delta) {
  
}
