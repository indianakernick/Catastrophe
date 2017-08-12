//
//  camera.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 30/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera.hpp"

#include "camera constants.hpp"

/*
tracking bounds is relative to the center of the window and the size of the
tracking bounds is relative to the size of the window
*/

Camera::Camera()
  : target(nullptr),
    center(),
    windowSize(DEFAULT_WINDOW_PIXEL_SIZE),
    trackingBounds(DEFAULT_TRACKING_BOUNDS),
    pixelsPerMeter(DEFAULT_PIXELS_PER_METER) {}

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
  if (target == nullptr) {
    return;
  }
  
  const glm::vec2 pxTrackingBounds = trackingBounds * static_cast<glm::vec2>(windowSize);
  const CameraTarget bounds(center, pxTrackingBounds / pixelsPerMeter);
  
  if (bounds.encloses(*target)) {
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
  
  center += motion;
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
  pixelsPerMeter = zoom;
}

float Camera::getZoom() const {
  return pixelsPerMeter;
}

glm::vec2 Camera::pixelsPerMeterPos() const {
  return {pixelsPerMeter, -pixelsPerMeter};
}

glm::vec2 Camera::halfWindowPixelSize() const {
  return windowSize / 2;
}
