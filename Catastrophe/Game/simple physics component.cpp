//
//  simple physics component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 3/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "simple physics component.hpp"

#include "../Libraries/Box2D/Dynamics/b2Body.h"

SimplePhysicsComponent::SimplePhysicsComponent(b2Body *const body)
  : body(body) {}

b2Vec2 SimplePhysicsComponent::getPos() const {
  return body->GetPosition();
}

b2Body *SimplePhysicsComponent::getBody() {
  return body;
}

const b2Body *SimplePhysicsComponent::getBody() const {
  return body;
}
