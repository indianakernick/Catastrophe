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
  const float mass,
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

void PhysicalObject::setRect(const Rect newRect) {
  rect = newRect;
}

void PhysicalObject::setMass(const float newMass) {
  mass = newMass;
}

void PhysicalObject::setCollidable(const bool newCollidable) {
  collidable = newCollidable;
}

void PhysicalObject::applyForce(const glm::vec2 newForce) {
  force += newForce;
}

void PhysicalObject::applyImpulse(const glm::vec2 newImpulse) {
  impulse += newImpulse;
}

void PhysicalObject::update(const float delta, const glm::vec2 grav) {
  if (mass == FIXED) {
    return;
  }
  
  accel = grav + force / mass;
  vel += accel * delta;
  vel += impulse / mass;
  rect.p += vel;
  force = {0.0f, 0.0f};
  impulse = {0.0f, 0.0f};
}

void PhysicalObject::onCollision(CollisionDispatcher::SettableListener listener) {
  collisionDispatcher.setListener(listener);
}

void PhysicalObject::offCollision() {
  collisionDispatcher.remListener();
}
