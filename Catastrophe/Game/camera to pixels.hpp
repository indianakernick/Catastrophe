//
//  camera to pixels.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 27/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef camera_to_pixels_hpp
#define camera_to_pixels_hpp

#include "rect.hpp"

struct CameraProps;

class CameraToPixels {
public:
  explicit CameraToPixels(CameraProps);
  CameraToPixels(const CameraToPixels &) = delete;
  CameraToPixels &operator=(const CameraToPixels &) = delete;
  CameraToPixels &operator=(CameraToPixels &&) = delete;
  
  int size(float) &&;
  glm::ivec2 size(glm::vec2) &&;
  glm::ivec2 size(float, float) &&;

  glm::ivec2 point(glm::vec2) &&;
  glm::ivec2 point(float, float) &&;
  
  RectPx rect(Rect) &&;
  std::pair<glm::ivec2, int> circle(glm::vec2, float) &&;
  std::pair<glm::ivec2, glm::ivec2> line(glm::vec2, glm::vec2) &&;
  
private:
  const glm::vec2 halfWindowSize;
  const glm::vec2 center;
  const float pixelsPerMeter;
  
  glm::vec2 pixelsPerMeterPos() &&;
  
  //Only Camera can move CameraToPixels in Camera::toPixels()
  friend class Camera;
  CameraToPixels(CameraToPixels &&) = default;
};

#endif
