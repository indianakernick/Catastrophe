//
//  camera motion track.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 27/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera motion track.hpp"

#include "rect.hpp"
#include "camera pos.hpp"
#include "camera props.hpp"
#include "camera constants.hpp"
#include "camera debug render constants.hpp"

CameraMotionTrack::CameraMotionTrack()
  : target(nullptr),
    localTarget(),
    center(DEFAULT_TRACKING_BOUNDS_CENTER),
    size(DEFAULT_TRACKING_BOUNDS_SIZE) {}

CameraMotionTrack::CameraMotionTrack(const CameraMotionTrack &other)
  : localTarget(other.localTarget),
    center(other.center),
    size(other.size) {
  if (other.target == &other.localTarget) {
    target = &localTarget;
  } else {
    target = other.target;
  }
}

CameraMotionTrack &CameraMotionTrack::operator=(const CameraMotionTrack &other) {
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

void CameraMotionTrack::start(const CameraMotionTarget *newTarget) {
  target = newTarget;
}

void CameraMotionTrack::stop() {
  target = nullptr;
}

bool CameraMotionTrack::hasTarget() const {
  return target;
}

const CameraMotionTarget *CameraMotionTrack::get() const {
  return target;
}

void CameraMotionTrack::setLocal(const CameraMotionTarget newTarget) {
  localTarget = newTarget;
}

void CameraMotionTrack::startLocal() {
  target = &localTarget;
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
  if (target == nullptr) {
    return props.center;
  }
  
  const CameraMotionTarget bounds(centerToMeters(props, center), sizeToMeters(props, size));
  
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
  
  if (target->halfSize.x > bounds.halfSize.x) {
    motion.x = target->center.x - bounds.center.x;
  }
  if (target->halfSize.y > bounds.halfSize.y) {
    motion.y = target->center.y - bounds.center.y;
  }
  
  return props.center + motion;
}

void CameraMotionTrack::debugRender(NVGcontext *context, const CameraProps props) const {
  const glm::vec2 corner = center - size / 2.0f;
  
  nvgSave(context);
    nvgResetTransform(context);
    nvgScale(context, props.windowSize.x, -props.windowSize.y);
    nvgTranslate(context, 0.5f, -0.5f);
    
    nvgBeginPath(context);
    nvgFillColor(context, CAMERA_TRACK_COLOR);
    nvgRect(context, corner.x, corner.y, size.x, size.y);
  
    nvgFill(context);
  nvgRestore(context);
  
  if (target) {
    const Rect targetRect = static_cast<Rect>(*target);
  
    nvgBeginPath(context);
    nvgFillColor(context, CAMERA_TARGET_COLOR);
    nvgRect(context, targetRect.p.x, targetRect.p.y, targetRect.s.x, targetRect.s.y);
    nvgFill(context);
  }
}

glm::vec2 CameraMotionTrack::centerToMeters(const CameraProps props, const glm::vec2 center) const {
  return props.center + sizeToMeters(props, center);
}

glm::vec2 CameraMotionTrack::sizeToMeters(const CameraProps props, const glm::vec2 size) const {
  return (size * static_cast<glm::vec2>(props.windowSize)) / props.pixelsPerMeter;
}
