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

OrthoMoveComponent::OrthoMoveComponent(const int moveSpeed)
  : freqLimiter(Time::OP_PER_SEC, moveSpeed) {}

void OrthoMoveComponent::startMoving(const Math::Dir dir) {
  if (moveDir != Math::Dir::NONE) {
    nextMoveDir = dir;
  } else {
    freqLimiter.reset();
    moveDir = dir;
  }
}

void OrthoMoveComponent::stopMoving() {
  nextMoveDir = Math::Dir::NONE;
}

bool OrthoMoveComponent::isMoving() const {
  return moveDir != Math::Dir::NONE;
}

Math::Dir OrthoMoveComponent::getMotionDir() const {
  return moveDir;
}

float OrthoMoveComponent::getMotionProgress() const {
  if (moveDir == Math::Dir::NONE) {
    return 0.0f;
  } else {
    return freqLimiter.getProgress<float>();
  }
}

void OrthoMoveComponent::update(EntityManager &entityMan, const uint64_t delta) {
  Entity &entity = getEntity();
  freqLimiter.advance(delta);
  
  if (moveDir != Math::Dir::NONE && freqLimiter.canDoOverlap()) {
    entity.rect.p += ToVec::conv(moveDir);
    entityMan.onEntityMove(&entity);
    if (nextMoveDir != Math::Dir::NONE) {
      const Rect nextRect = {entity.rect.p + ToVec::conv(nextMoveDir), entity.rect.s};
      if (entityMan.entityCanMoveTo(&entity, nextRect)) {
        moveDir = nextMoveDir;
      } else {
        moveDir = Math::Dir::NONE;
      }
    } else {
      moveDir = Math::Dir::NONE;
    }
  }
}
