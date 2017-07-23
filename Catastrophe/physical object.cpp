//
//  physical object.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 23/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "physical object.hpp"

PhysicalObject::PhysicalObject(
  const EntityID entity,
  const Rect rect,
  const unsigned mass,
  const bool collidable
) : entity(entity),
    rect(rect),
    mass(mass),
    collidable(collidable) {}

EntityID PhysicalObject::getID() const {
  return entity;
}

Rect PhysicalObject::getRect() const {
  return rect;
}

void PhysicalObject::setVelocity(const glm::vec2 dir) {
  vel = dir;
}

void PhysicalObject::onCollision(CollisionDispatcher::SettableListener listener) {
  collisionDispatcher.setListener(listener);
}

void PhysicalObject::offCollision() {
  collisionDispatcher.remListener();
}
