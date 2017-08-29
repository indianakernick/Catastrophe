//
//  camera to meters.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 27/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef camera_to_meters_hpp
#define camera_to_meters_hpp

#include "rect.hpp"

struct CameraProps;

class CameraToMeters {
public:
  explicit CameraToMeters(CameraProps);
  CameraToMeters(const CameraToMeters &) = delete;
  CameraToMeters &operator=(const CameraToMeters &) = delete;
  CameraToMeters &operator=(CameraToMeters &&) = delete;
  
  float size(int) &&;
  glm::vec2 size(glm::ivec2) &&;
  glm::vec2 size(int, int) &&;

  glm::vec2 point(glm::ivec2) &&;
  glm::vec2 point(int, int) &&;
  
  Rect rect(RectPx) &&;
  std::pair<glm::vec2, float> circle(glm::ivec2, int) &&;
  std::pair<glm::vec2, glm::vec2> line(glm::ivec2, glm::ivec2) &&;
  
private:
  const glm::vec2 halfWindowSize;
  const glm::vec2 center;
  const float pixelsPerMeter;
  
  glm::vec2 pixelsPerMeterPos() &&;
  
  //Only Camera can move CameraToMeters in Camera::toMeters()
  friend class Camera;
  CameraToMeters(CameraToMeters &&) = default;
};

#endif
