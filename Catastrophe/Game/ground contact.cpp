//
//  ground contact.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "ground contact.hpp"

#include "../Libraries/Box2D/Dynamics/b2Body.h"

void GroundContact::beginContactingGround(b2Body *const body) {
  groundBodies.push_back(body);
}

void GroundContact::endContactingGround(b2Body *const body) {
  const auto bodyIter = std::find(groundBodies.cbegin(), groundBodies.cend(), body);
  if (bodyIter == groundBodies.cend()) {
    throw std::runtime_error("Ended a ground contact that didn't begin");
  }
  groundBodies.erase(bodyIter);
}

b2Vec2 GroundContact::getGroundVel() const {
  if (groundBodies.empty()) {
    return {0.0f, 0.0f};
  } else {
    return groundBodies.front()->GetLinearVelocity();
  }
}

bool GroundContact::onGround() const {
  return groundBodies.size();
}
