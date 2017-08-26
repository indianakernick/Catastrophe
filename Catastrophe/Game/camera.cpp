//
//  camera.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 30/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera.hpp"

#include <SDL2/SDL_rect.h>
#include "input system.hpp"
#include <glm/gtx/norm.hpp>
#include <SDL2/SDL_events.h>
#include "camera constants.hpp"
#include "rendering context.hpp"
#include <Simpleton/Math/scale.hpp>

/*
tracking bounds is relative to the center of the window and the size of the
tracking bounds is relative to the size of the window
*/

Camera::Camera()
  : windowSize(DEFAULT_WINDOW_PIXEL_SIZE),
    trackingBoundsCenter(DEFAULT_TRACKING_BOUNDS_CENTER),
    trackingBoundsSize(DEFAULT_TRACKING_BOUNDS_SIZE),
    pixelsPerMeter(DEFAULT_PIXELS_PER_METER),
    zoomTarget(pixelsPerMeter),
    lastMotionTarget(center),
    motionTarget(center) {}

int Camera::sizeToPixels(const float s) const {
  return s * pixelsPerMeter;
}

glm::ivec2 Camera::sizeToPixels(const glm::vec2 s) const {
  return s * pixelsPerMeter;
}

glm::ivec2 Camera::sizeToPixels(const float w, const float h) const {
  return sizeToPixels({w, h});
}

glm::ivec2 Camera::posToPixels(const glm::vec2 p) const {
  return (p - center) * pixelsPerMeterPos() + halfWindowPixelSize();
}

glm::ivec2 Camera::posToPixels(const float x, const float y) const {
  return posToPixels({x, y});
}

RectPx Camera::rectToPixels(const Rect rect) const {
  const glm::ivec2 pos = posToPixels(rect.p);
  const glm::ivec2 size = sizeToPixels(rect.s);
  return {{pos.x, pos.y - size.y}, size};
}

float Camera::sizeToMeters(const int s) const {
  return static_cast<float>(s) / pixelsPerMeter;
}

glm::vec2 Camera::sizeToMeters(const glm::ivec2 s) const {
  return static_cast<glm::vec2>(s) / pixelsPerMeter;
}

glm::vec2 Camera::sizeToMeters(const int w, const int h) const {
  return sizeToMeters({w, h});
}

glm::vec2 Camera::posToMeters(const glm::ivec2 p) const {
  return
    (static_cast<glm::vec2>(p) - halfWindowPixelSize()) /
    pixelsPerMeterPos() + center
  ;
}

glm::vec2 Camera::posToMeters(const int x, const int y) const {
  return posToMeters({x, y});
}

Rect Camera::rectToMeters(const RectPx rect) const {
  const glm::vec2 pos = posToMeters(rect.p);
  const glm::vec2 size = sizeToMeters(rect.s);
  return {{pos.x, pos.y + size.y}, size};
}

bool Camera::visible(const int x, const int y) const {
  return RectPx(windowSize).encloses({x, y});
}

bool Camera::visible(const glm::ivec2 p) const {
  return RectPx(windowSize).encloses(p);
}

bool Camera::visible(const RectPx r) const {
  return RectPx(windowSize).interceptsWith(r);
}

bool Camera::visible(const glm::ivec2 p, const int r) const {
  //https://stackoverflow.com/a/402010
  
  const glm::ivec2 HALF_WINDOW_PIXEL_SIZE = windowSize / 2;
  
  //distance between center of circle and center of rectangle (window)
  const glm::ivec2 centerDist = {
    std::abs(p.x - HALF_WINDOW_PIXEL_SIZE.x),
    std::abs(p.y - HALF_WINDOW_PIXEL_SIZE.y)
  };
  
  if (centerDist.x > HALF_WINDOW_PIXEL_SIZE.x + r) return false;
  if (centerDist.y > HALF_WINDOW_PIXEL_SIZE.y + r) return false;
  
  if (centerDist.x <= HALF_WINDOW_PIXEL_SIZE.x) return true;
  if (centerDist.y <= HALF_WINDOW_PIXEL_SIZE.y) return true;
  
  auto square = [] (const int n) {
    return n * n;
  };
  
  //squared distance between center of circle and corner
  const int cornerDist = square(centerDist.x - HALF_WINDOW_PIXEL_SIZE.x) +
                         square(centerDist.y - HALF_WINDOW_PIXEL_SIZE.y);
  return cornerDist <= square(r);
}

bool Camera::visible(glm::ivec2 p0, glm::ivec2 p1) const {
  const SDL_Rect windowRect = {0, 0, windowSize.x, windowSize.y};
  return SDL_IntersectRectAndLine(&windowRect, &p0.x, &p0.y, &p1.x, &p1.y);
}

void Camera::update(const float delta) {
  track();
  animateMove(delta);
  animateZoom(delta);
}

void Camera::debugRender() {
  if (renderer == nullptr) {
    return;
  }
  
  const glm::vec2 centerM = center + trackingBoundsToMeters(trackingBoundsCenter);
  const glm::vec2 sizeM = trackingBoundsToMeters(trackingBoundsSize);
  const glm::vec2 cornerM = centerM - sizeM / 2.0f;
  renderer->renderRect(CAM_TRACK_COLOR, {cornerM, sizeM});
  
  if (target) {
    renderer->renderRect(CAM_TARGET_COLOR, static_cast<Rect>(*target));
  }
}

void Camera::attachRenderer(RenderingContext &newRenderer) {
  renderer = &newRenderer;
}

void Camera::detachRenderer() {
  renderer = nullptr;
}

void Camera::addEventListener(InputSystem &inputSystem) {
  assert(listenerID == 0xFFFFFFFF);
  listenerID = inputSystem.addListener(Utils::memFunWrap(this, &Camera::eventListener));
}

void Camera::remEventListener(InputSystem &inputSystem) {
  assert(listenerID != 0xFFFFFFFF);
  inputSystem.remListener(listenerID);
}

void Camera::setTrackingBounds(const glm::vec2 newCenter, const glm::vec2 newSize) {
  trackingBoundsCenter = newCenter;
  trackingBoundsSize = newSize;
}

void Camera::trackTarget(const CameraTarget *newTarget) {
  target = newTarget;
}

void Camera::stopTracking() {
  target = nullptr;
}

const CameraTarget *Camera::getTarget() const {
  return target;
}

void Camera::moveTo(const glm::vec2 pos) {
  center = pos;
}

glm::vec2 Camera::getPos() const {
  return {};
}

void Camera::zoomTo(const float zoom) {
  assert(zoom >= MIN_ZOOM);
  assert(zoom <= MAX_ZOOM);
  
  zoomTarget = zoom;
}

float Camera::getZoom() const {
  return pixelsPerMeter;
}

bool Camera::eventListener(const SDL_Event &event) {
  if (event.type != SDL_WINDOWEVENT) {
    return false;
  }
  
  const SDL_WindowEvent &winEvent = event.window;
  
  if (winEvent.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
    windowSize = {winEvent.data1, winEvent.data2};
    return true;
  } else {
    return false;
  }
}

glm::vec2 Camera::pixelsPerMeterPos() const {
  return {pixelsPerMeter, -pixelsPerMeter};
}

glm::vec2 Camera::halfWindowPixelSize() const {
  return windowSize / 2;
}

glm::vec2 Camera::trackingBoundsToMeters(const glm::vec2 v) const {
  return (v * static_cast<glm::vec2>(windowSize)) / pixelsPerMeter;
}

void Camera::track() {
  if (target == nullptr) {
    return;
  }
  
  const glm::vec2 centerM = trackingBoundsToMeters(trackingBoundsCenter);
  const glm::vec2 sizeM = trackingBoundsToMeters(trackingBoundsSize);
  const CameraTarget bounds(center + centerM, sizeM);
  
  lastMotionTarget = motionTarget;
  
  if (bounds.encloses(*target)) {
    motionTarget = center;
    return;
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
  
  motionTarget = center + motion;
}

void Camera::animateMove(const float delta) {
  glm::vec2 desired = motionTarget - center;
  const float distance = glm::length(desired);
  if (distance != 0.0f) {
    desired /= distance;
  }
  
  if (distance <= MOVE_SLOW_DIST) {
    desired *= Math::scale(distance, 0.0f, MOVE_SLOW_DIST, 0.0f, MAX_MOVE_VEL);
  } else {
    desired *= MAX_MOVE_VEL;
  }
  
  glm::vec2 steer = desired - motionVel;
  if (glm::length2(steer) > MAX_MOVE_FORCE * MAX_MOVE_FORCE) {
    steer = glm::normalize(steer);
    steer *= MAX_MOVE_FORCE;
  }
  
  if (
    glm::length2(motionVel) <= MOVE_STOP_VEL * MOVE_STOP_VEL &&
    distance <= MOVE_STOP_DIST &&
    motionTarget == lastMotionTarget
  ) {
    motionVel = {0.0f, 0.0f};
    center = motionTarget;
  } else {
    motionVel += steer;
    center += motionVel * delta;
  }
}

void Camera::animateZoom(const float delta) {
  float desired = zoomTarget - pixelsPerMeter;
  const float distance = std::abs(desired);
  if (distance != 0.0f) {
    desired /= distance;
  }
  
  if (distance <= ZOOM_SLOW_DIST) {
    desired *= Math::scale(distance, 0.0f, ZOOM_SLOW_DIST, 0.0f, MAX_ZOOM_VEL);
  } else {
    desired *= MAX_ZOOM_VEL;
  }
  
  float steer = desired - zoomVel;
  if (std::abs(steer) > MAX_ZOOM_FORCE) {
    steer = Math::sign(steer) * MAX_ZOOM_FORCE;
  }
 
  if (std::abs(zoomVel) <= ZOOM_STOP_VEL && distance <= ZOOM_STOP_DIST) {
    zoomVel = 0.0f;
    pixelsPerMeter = zoomTarget;
  } else {
    zoomVel += steer;
    pixelsPerMeter += zoomVel * delta;
  }
}
