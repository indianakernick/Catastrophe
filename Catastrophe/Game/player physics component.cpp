//
//  player physics component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 3/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "player physics component.hpp"

#include "../Libraries/Box2D/Dynamics/b2Body.h"

PlayerPhysicsComponent::PlayerPhysicsComponent(b2Body *body)
  : body(body) {
  assert(body);
}

b2Vec2 PlayerPhysicsComponent::getPos() const {
  return body->GetPosition();
}

b2Body *PlayerPhysicsComponent::getBody() {
  return body;
}

const b2Body *PlayerPhysicsComponent::getBody() const {
  return body;
}

bool PlayerPhysicsComponent::onGround() const {
  return footContactCount > 0;
}

void PlayerPhysicsComponent::beginContactingGround() {
  footContactCount++;
}

void PlayerPhysicsComponent::endContactingGround() {
  footContactCount--;
}
