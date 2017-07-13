//
//  ortho move entity.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 13/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "ortho move entity.hpp"

#include "dir to vec.hpp"
#include "entity manager.hpp"

OrthoMoveEntity::OrthoMoveEntity(const EntityID id, const Rect rect, const int moveSpeed)
  : Entity(id, rect), freqLimiter(Time::OP_PER_SEC, moveSpeed) {}

void OrthoMoveEntity::startMoving(const Math::Dir dir) {
  if (moving) {
    nextMoveDir = dir;
    hasNextMoveDir = true;
  } else {
    freqLimiter.reset();
    moveDir = dir;
    moving = true;
  }
}

void OrthoMoveEntity::stopMoving() {
  hasNextMoveDir = false;
}

bool OrthoMoveEntity::isMoving() const {
  return moving;
}

Math::Dir OrthoMoveEntity::getMotionDir() const {
  return moveDir;
}

float OrthoMoveEntity::getMotionProgress() const {
  if (moving) {
    return static_cast<float>(freqLimiter.getTimeSinceLast()) / freqLimiter.getDuration();
  } else {
    return 0.0f;
  }
}

void OrthoMoveEntity::update(EntityManager &entityMan, const uint64_t delta) {
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
