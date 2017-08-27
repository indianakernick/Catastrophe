//
//  camera track.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 27/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera track.hpp"

#include "camera pos.hpp"
#include "camera constants.hpp"
#include "rendering context.hpp"
#include "camera scale tracking bounds.hpp"

CameraTrack::CameraTrack()
  : target(nullptr),
    center(DEFAULT_TRACKING_BOUNDS_CENTER),
    size(DEFAULT_TRACKING_BOUNDS_SIZE) {}

void CameraTrack::start(const CameraTarget *newTarget) {
  target = newTarget;
}

void CameraTrack::stop() {
  target = nullptr;
}

const CameraTarget *CameraTrack::get() const {
  return target;
}

void CameraTrack::setBounds(const glm::vec2 newCenter, const glm::vec2 newSize) {
  center = newCenter;
  size = newSize;
}

void CameraTrack::setTargetPos(CameraPos &pos, const CameraScaleTrackingBounds scale) {
  if (target == nullptr) return;
  
  const CameraTarget bounds(scale.centerToMeters(center), scale.sizeToMeters(size));
  
  if (bounds.encloses(*target)) {
    return pos.setMoving(pos.get());
  }

  glm::vec2 motion = {0.0f, 0.0f};
  
  if (const float moveUp    = target->top   () - bounds.top   (); moveUp    > 0.0f) {
    motion.y = moveUp;
  }
  if (const float moveRight = target->right () - bounds.right (); moveRight > 0.0f) {
    motion.x = moveRight;
  }
  if (const float moveDown  = target->bottom() - bounds.bottom(); moveDown  < 0.0f) {
    motion.y = moveDown;
  }
  if (const float moveLeft  = target->left  () - bounds.left  (); moveLeft  < 0.0f) {
    motion.x = moveLeft;
  }
  
  pos.setMoving(pos.get() + motion);
}

void CameraTrack::debugRender(
  RenderingContext &renderer,
  const CameraScaleTrackingBounds scale
) const {
  const glm::vec2 centerM = scale.centerToMeters(center);
  const glm::vec2 sizeM = scale.sizeToMeters(size);
  const glm::vec2 cornerM = centerM - sizeM / 2.0f;
  renderer.renderRect(CAM_TRACK_COLOR, {cornerM, sizeM});
  
  if (target) {
    renderer.renderRect(CAM_TARGET_COLOR, static_cast<Rect>(*target));
  }
}
