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
  : Entity(id), freqLimiter(Time::OP_PER_SEC, moveSpeed), rect(rect) {}

void SimpleEntity::startMoving(const Math::Dir dir) {
  if (moving) {
    nextMoveDir = dir;
    hasNextMoveDir = true;
  } else {
    freqLimiter.reset();
    moveDir = dir;
    moving = true;
  }
}

void SimpleEntity::stopMoving() {
  hasNextMoveDir = false;
}

Rect SimpleEntity::getRect() const {
  return rect;
}

bool SimpleEntity::isMoving() const {
  return moving;
}

Math::Dir SimpleEntity::getMotionDir() const {
  return moveDir;
}

float SimpleEntity::getMotionProgress() const {
  if (moving) {
    return static_cast<float>(freqLimiter.getTimeSinceLast()) / freqLimiter.getDuration();
  } else {
    return 0.0f;
  }
}

void SimpleEntity::update(EntityManager &entityMan, const uint64_t delta) {
  freqLimiter.advance(delta);
  
  if (moving && freqLimiter.canDoOverlap()) {
    rect.p += ToVec::conv(moveDir);
    entityMan.onEntityMove(this);
    if (hasNextMoveDir) {
      const Rect nextRect = {rect.p + ToVec::conv(nextMoveDir), rect.s};
      if (entityMan.entityCanMoveTo(this, nextRect)) {
        moveDir = nextMoveDir;
      } else {
        moving = false;
      }
    } else {
      moving = false;
    }
  }
}

bool SimpleEntity::entityCanCollide(Entity *) {
  return false;
}

void SimpleEntity::onEntityCollision(Entity *) {
  
}

void SimpleEntity::onCollisionWithEntity(Entity *) {

}
