//
//  ground droid physics component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "ground droid physics component.hpp"

#include "../Libraries/Box2D/Dynamics/b2Body.h"

float GroundDroidPhysicsComponent::getVelX() const {
  //I don't think there's any point in getting the velocity relative to the
  //ground like PlayerPhysicsComponent does.
  return body->GetLinearVelocity().x;
}
