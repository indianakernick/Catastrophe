//
//  simple entity.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "simple entity.hpp"

#include "dir to vec.hpp"
#include "entity manager.hpp"

SimpleEntity::SimpleEntity(const EntityID id, const Rect rect, const int moveSpeed)
  : OrthoMoveEntity(id, rect, moveSpeed) {}

void SimpleEntity::update(EntityManager &entityMan, const uint64_t delta) {
  OrthoMoveEntity::update(entityMan, delta);
}

bool SimpleEntity::entityCanCollide(Entity *) {
  return false;
}

void SimpleEntity::onEntityCollision(Entity *) {
  
}

void SimpleEntity::onCollisionWithEntity(Entity *) {

}
