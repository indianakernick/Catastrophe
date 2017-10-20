//
//  camera motion track.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 27/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera motion track.hpp"

#include "camera pos.hpp"
#include "camera props.hpp"
#include "camera constants.hpp"

CameraMotionTrack::CameraMotionTrack()
  : target(),
    localTarget(makeMotionTarget()),
    center(DEFAULT_TRACKING_BOUNDS_CENTER),
    size(DEFAULT_TRACKING_BOUNDS_SIZE) {}

void CameraMotionTrack::start(const CameraMotionTargetCPtr newTarget) {
  target = newTarget;
}

void CameraMotionTrack::stop() {
  target.reset();
}

void CameraMotionTrack::setLocal(const CameraMotionTarget newTarget) {
  *localTarget = newTarget;
}

void CameraMotionTrack::startLocal() {
  target = localTarget;
}

void CameraMotionTrack::setAndStartLocal(const CameraMotionTarget newTarget) {
  setLocal(newTarget);
  startLocal();
}

void CameraMotionTrack::setBounds(const glm::vec2 newCenter, const glm::vec2 newSize) {
  center = newCenter;
  size = newSize;
}

glm::vec2 CameraMotionTrack::calcMotionTarget(const CameraProps props) const {
  const auto targetShared = target.lock();
  if (targetShared == nullptr) {
    return props.center;
  }
  const CameraMotionTarget targetObj = *targetShared;
  
  const CameraMotionTarget bounds(centerToMeters(props, center), sizeToMeters(props, size));
  
  if (bounds.encloses(targetObj)) {
    return props.center;
  }

  glm::vec2 motion = {0.0f, 0.0f};
  
  if (const float moveUp    = targetObj.top   () - bounds.top   (); moveUp    > 0.0f) {
    motion.y = moveUp;
  }
  if (const float moveRight = targetObj.right () - bounds.right (); moveRight > 0.0f) {
    motion.x = moveRight;
  }
  if (const float moveDown  = targetObj.bottom() - bounds.bottom(); moveDown  < 0.0f) {
    motion.y = moveDown;
  }
  if (const float moveLeft  = targetObj.left  () - bounds.left  (); moveLeft  < 0.0f) {
    motion.x = moveLeft;
  }
  
  if (targetObj.halfSize.x > bounds.halfSize.x) {
    motion.x = targetObj.center.x - bounds.center.x;
  }
  if (targetObj.halfSize.y > bounds.halfSize.y) {
    motion.y = targetObj.center.y - bounds.center.y;
  }
  
  return props.center + motion;
}

CameraMotionTrack::RenderingData CameraMotionTrack::getRenderingData() const {
  RenderingData renderingData;
  renderingData.bounds.center = center;
  renderingData.bounds.halfSize = size / 2.0f;
  const auto targetShared = target.lock();
  if (targetShared) {
    renderingData.target.emplace(*targetShared);
  }
  return renderingData;
}

glm::vec2 CameraMotionTrack::centerToMeters(const CameraProps props, const glm::vec2 center) const {
  return props.center + sizeToMeters(props, center);
}

glm::vec2 CameraMotionTrack::sizeToMeters(const CameraProps props, const glm::vec2 size) const {
  return (size * static_cast<glm::vec2>(props.windowSize)) / props.pixelsPerMeter;
}
