//
//  physics component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "physics component.hpp"

#include <cassert>

PhysicsComponent::PhysicsComponent(
  Entity *const entity,
  b2Body *const body
) : Component(entity),
    body(body) {
  assert(body);
}
