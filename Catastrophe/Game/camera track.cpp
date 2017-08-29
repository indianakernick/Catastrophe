//
//  camera track.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 27/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera track.hpp"

#include "camera pos.hpp"
#include "camera props.hpp"
#include "camera constants.hpp"
#include "rendering context.hpp"

CameraTrack::CameraTrack()
  : target(nullptr),
    localTarget(),
    center(DEFAULT_TRACKING_BOUNDS_CENTER),
    size(DEFAULT_TRACKING_BOUNDS_SIZE) {}

CameraTrack::CameraTrack(const CameraTrack &other)
  : localTarget(other.localTarget),
    center(other.center),
    size(other.size) {
  if (other.target == &other.localTarget) {
    target = &localTarget;
  } else {
    target = other.target;
  }
}

CameraTrack &CameraTrack::operator=(const CameraTrack &other) {
  if (other.target == &other.localTarget) {
    target = &localTarget;
  } else {
    target = other.target;
  }
  
  localTarget = other.localTarget;
  center = other.center;
  size = other.size;
  
  return *this;
}

void CameraTrack::start(const CameraTarget *newTarget) {
  target = newTarget;
}

void CameraTrack::stop() {
  target = nullptr;
}

bool CameraTrack::hasTarget() const {
  return target != nullptr;
}

const CameraTarget *CameraTrack::get() const {
  return target;
}

void CameraTrack::setLocal(const CameraTarget newTarget) {
  localTarget = newTarget;
}

void CameraTrack::startLocal() {
  target = &localTarget;
}

void CameraTrack::setBounds(const glm::vec2 newCenter, const glm::vec2 newSize) {
  center = newCenter;
  size = newSize;
}

glm::vec2 CameraTrack::calcMotionTarget(const CameraProps props) const {
  if (target == nullptr) {
    return props.center;
  }
  
  const CameraTarget bounds(centerToMeters(props, center), sizeToMeters(props, size));
  
  if (bounds.encloses(*target)) {
    return props.center;
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
  
  return props.center + motion;
}

glm::vec2 CameraTrack::centerToMeters(const CameraProps props, const glm::vec2 center) const {
  return props.center + sizeToMeters(props, center);
}

glm::vec2 CameraTrack::sizeToMeters(const CameraProps props, const glm::vec2 size) const {
  return (size * static_cast<glm::vec2>(props.windowSize)) / props.pixelsPerMeter;
}

void CameraTrack::debugRender(
  const CameraProps props,
  RenderingContext &renderer
) const {
  const glm::vec2 centerM = centerToMeters(props, center);
  const glm::vec2 sizeM = sizeToMeters(props, size);
  const glm::vec2 cornerM = centerM - sizeM / 2.0f;
  renderer.renderRect(CAM_TRACK_COLOR, {cornerM, sizeM});
  
  if (target) {
    renderer.renderRect(CAM_TARGET_COLOR, static_cast<Rect>(*target));
  }
}
