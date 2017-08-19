//
//  camera.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 30/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera.hpp"

#include <iostream>
#include <glm/gtx/norm.hpp>
#include "camera constants.hpp"
#include <Simpleton/Math/scale.hpp>

/*
tracking bounds is relative to the center of the window and the size of the
tracking bounds is relative to the size of the window
*/

Camera::Camera()
  : windowSize(DEFAULT_WINDOW_PIXEL_SIZE),
    trackingBounds(DEFAULT_TRACKING_BOUNDS),
    pixelsPerMeter(DEFAULT_PIXELS_PER_METER),
    zoomTarget(pixelsPerMeter),
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
  //a few false positives are ok
  //could use SDL_IntersectRectAndLine for better accuracy
  
  if (p0.x > p1.x) {
    std::swap(p0.x, p1.x);
  }
  if (p0.y > p1.y) {
    std::swap(p0.y, p1.y);
  }
  return RectPx(windowSize).interceptsWith(RectPx(p0, p1 - p0));
}

void Camera::update(const float delta) {
  track();
  animateMove(delta);
  animateZoom(delta);
}

void Camera::setTrackingBounds(const glm::vec2 newTrackingBounds) {
  trackingBounds = newTrackingBounds;
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

void Camera::print() const {
  std::cout.precision(10);
  std::cout << "Camera {\n";
  std::cout << "  center:         {" << center.x << ", " << center.y << "},\n";
  std::cout << "  windowSize:     {" << windowSize.x << ", " << windowSize.y << "},\n";
  std::cout << "  trackingBounds: {" << trackingBounds.x << ", " << trackingBounds.y << "},\n";
  std::cout << "  pixelsPerMeter: " << pixelsPerMeter << ",\n";
  std::cout << "  zoomVel:        " << zoomVel << ",\n";
  std::cout << "  zoomTarget:     " << zoomTarget << ",\n";
  std::cout << "  motionVel:      {" << motionVel.x << ", " << motionVel.y << "},\n";
  std::cout << "  motionTarget:   {" << motionTarget.x << ", " << motionTarget.y << "}\n";
  std::cout << "}";
}

glm::vec2 Camera::pixelsPerMeterPos() const {
  return {pixelsPerMeter, -pixelsPerMeter};
}

glm::vec2 Camera::halfWindowPixelSize() const {
  return windowSize / 2;
}

void Camera::track() {
  if (target == nullptr) {
    return;
  }
  
  const glm::vec2 pxTrackingBounds = trackingBounds * static_cast<glm::vec2>(windowSize);
  const CameraTarget bounds(center, pxTrackingBounds / pixelsPerMeter);
  
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
    distance <= MOVE_STOP_DIST
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
