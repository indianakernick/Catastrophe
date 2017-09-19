//
//  simple physics component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 3/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "simple physics component.hpp"

#include "entity.hpp"
#include "physics state.hpp"
#include "../Libraries/Box2D/Dynamics/b2Body.h"

SimplePhysicsComponent::SimplePhysicsComponent(
  Entity *const entity,
  b2Body *body
) : PhysicsComponent(entity, body) {}

void SimplePhysicsComponent::preStep(float) {}

void SimplePhysicsComponent::postStep() {
  auto &physics = *getEntity().latestPhysicsState;
  physics.pos = body->GetPosition();
}
