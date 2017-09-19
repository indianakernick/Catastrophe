//
//  simple physics component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 3/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "simple physics component.hpp"

#include "physics state.hpp"
#include "../Libraries/Box2D/Dynamics/b2Body.h"

SimplePhysicsComponent::SimplePhysicsComponent(
  Entity *const entity,
  b2Body *body
) : PhysicsComponent(entity, body) {}

void SimplePhysicsComponent::preStep(PhysicsState &, const InputCommands &, float) {}

void SimplePhysicsComponent::postStep(PhysicsState &physics, const InputCommands &) {
  physics.pos = body->GetPosition();
}
