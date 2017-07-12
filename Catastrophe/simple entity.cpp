//
//  simple entity.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "simple entity.hpp"

SimpleEntity::SimpleEntity(const EntityID id, const Rect rect, const int moveSpeed)
  : Entity(id), freqLimiter(Time::OP_PER_SEC, moveSpeed), rect(rect) {}

void SimpleEntity::startMoving(const Math::Dir dir) {
  nextMoveDir = dir;
  hasNextMoveDir = true;
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

void SimpleEntity::update(const uint64_t delta) {
  using ToVec = Math::ToVec<Rect::Scalar, Math::Dir::RIGHT, Math::Dir::DOWN>;
  
  freqLimiter.advance(delta);
  
  if (freqLimiter.canDoOverlap()) {
    if (moving) {
      rect.p += ToVec::conv(moveDir);
    }
    moving = hasNextMoveDir;
    nextMoveDir = moveDir;
  }
}
