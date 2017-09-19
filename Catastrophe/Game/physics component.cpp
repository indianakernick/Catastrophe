//
//  physics component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "physics component.hpp"

#include <cassert>
#include "b2 glm cast.hpp"
#include "../Libraries/Box2D/Dynamics/b2Body.h"

PhysicsComponent::PhysicsComponent(
  Entity *const entity,
  b2Body *const body
) : Component(entity),
    body(body) {
  assert(body);
}

glm::vec2 PhysicsComponent::getPos() const {
  return castToGLM(body->GetPosition());
}
