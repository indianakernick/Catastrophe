//
//  camera.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 20/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera.hpp"

#include "entity.hpp"
#include <glm/glm.hpp>
#include "window constants.hpp"
#include <Simpleton/Math/interpolate.hpp>
#include <Simpleton/Utils/member function.hpp>

uint64_t fromSeconds(const float seconds) {
  //Animations are done in microseconds
  return seconds * 1'000'000.0f;
}

Camera::Camera()
  : anim(0, Time::DeltaAnim::PAUSE) {}

Camera::Camera(const glm::vec2 pos)
  : currPos(pos), anim(0, Time::DeltaAnim::PAUSE) {}

void Camera::update(const float delta) {
  anim.advance(fromSeconds(delta));
  if (anim.isPaused()) {
    currPos = nextPos;
    anim.stop();
  }
}

void Camera::setTarget(Entity &entity) {
  entity.onMove(Utils::memFunWrap(this, &Camera::onTargetMove));
}

void Camera::unsetTarget(Entity &entity) {
  entity.offMove();
}

void Camera::moveTo(const glm::vec2 newPos) {
  if (anim.isRunning()) {
    anim.stop();
  }
  currPos = newPos;
}

void Camera::moveInTime(const glm::vec2 newPos, const float duration) {
  if (anim.isRunning()) {
    currPos = getPos();
    nextPos = newPos;
    anim.stop();
    anim.setDuration(fromSeconds(duration));
    anim.start();
  } else {
    nextPos = newPos;
    anim.setDuration(fromSeconds(duration));
    anim.start();
  }
}

RectPx Camera::transform(const Rect rect) const {
  static const glm::vec2 HALF_WINDOW_TILE_SIZE = WINDOW_TILE_SIZE / 2.0f;
  const glm::vec2 topLeftPos = getPos() - HALF_WINDOW_TILE_SIZE;
  return {
    static_cast<int>((rect.p.x - topLeftPos.x) * PIXELS_PER_TILE.x),
    static_cast<int>((rect.p.y - topLeftPos.y) * PIXELS_PER_TILE.y),
    static_cast<int>(rect.s.x * PIXELS_PER_TILE.x),
    static_cast<int>(rect.s.y * PIXELS_PER_TILE.y)
  };
}

glm::vec2 Camera::getPos() const {
  if (anim.isRunning()) {
    return glm::mix(currPos, nextPos, Math::sinInOut(anim.getProgress()));
  } else {
    return currPos;
  }
}

void Camera::onTargetMove(const Rect, const Rect currRect) {
  const glm::vec2 targetPos = currRect.p + currRect.s / 2.0f;
  if constexpr (RIGID) {
    moveTo(targetPos);
  } else {
    moveTo(glm::mix(currPos, targetPos, MOVE_TARGET_PERCENT));
    moveInTime(targetPos, MOVE_TARGET_TIME);
  }
}
