//
//  camera.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 30/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef camera_hpp
#define camera_hpp

#include "rect.hpp"

using CameraTarget = Math::RectCS<float, Math::Dir::RIGHT, Math::Dir::UP>;

class RenderingContext;

class Camera {
public:
  Camera();
  ~Camera() = default;
  
  //meters to pixels
  int sizeToPixels(float) const;
  glm::ivec2 sizeToPixels(glm::vec2) const;
  glm::ivec2 sizeToPixels(float, float) const;

  glm::ivec2 posToPixels(glm::vec2) const;
  glm::ivec2 posToPixels(float, float) const;
  
  RectPx rectToPixels(Rect) const;
  
  //pixels to meters
  float sizeToMeters(int) const;
  glm::vec2 sizeToMeters(glm::ivec2) const;
  glm::vec2 sizeToMeters(int, int) const;

  glm::vec2 posToMeters(glm::ivec2) const;
  glm::vec2 posToMeters(int, int) const;
  
  Rect rectToMeters(RectPx) const;
  
  ///Point
  bool visible(int, int) const;
  ///Point
  bool visible(glm::ivec2) const;
  ///Rectangle
  bool visible(RectPx) const;
  ///Circle
  bool visible(glm::ivec2, int) const;
  ///Line
  bool visible(glm::ivec2, glm::ivec2) const;

  void update(float);
  void debugRender();
  
  void attachRenderer(RenderingContext &);
  void detachRenderer();
  
  void setTrackingBounds(glm::vec2, glm::vec2);

  void trackTarget(const CameraTarget *);
  void stopTracking();
  const CameraTarget *getTarget() const;
  
  void moveTo(glm::vec2);
  glm::vec2 getPos() const;
  
  void zoomTo(float);
  float getZoom() const;

private:
  const CameraTarget *target = nullptr;
  glm::vec2 center = {0.0f, 0.0f};
  glm::ivec2 windowSize;
  //relative to the center of the camera in units that are the size of the window
  glm::vec2 trackingBoundsCenter;
  //in units that are the size of the window
  glm::vec2 trackingBoundsSize;
  float pixelsPerMeter;
  
  float zoomVel = 0.0f;
  float zoomTarget;
  
  RenderingContext *renderer = nullptr;
  
  glm::vec2 motionVel = {0.0f, 0.0f};
  glm::vec2 motionTarget;
  
  glm::vec2 pixelsPerMeterPos() const;
  glm::vec2 halfWindowPixelSize() const;
  
  glm::vec2 trackingBoundsToMeters(glm::vec2) const;
  
  void track();
  void animateMove(float);
  void animateZoom(float);
};

#endif
