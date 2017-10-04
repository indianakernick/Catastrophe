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

glm::vec2 PhysicsComponent::getPos() const {
  assert(body);
  return castToGLM(body->GetPosition());
}

float PhysicsComponent::getAngle() const {
  assert(body);
  return body->GetAngle();
}
