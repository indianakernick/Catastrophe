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
  
  float size(int) const;
  glm::vec2 size(glm::ivec2) const;
  glm::vec2 size(int, int) const;

  glm::vec2 point(glm::ivec2) const;
  glm::vec2 point(int, int) const;
  
  Rect rect(RectPx) const;
  std::pair<glm::vec2, float> circle(glm::ivec2, int) const;
  std::pair<glm::vec2, glm::vec2> line(glm::ivec2, glm::ivec2) const;
  
private:
  glm::vec2 halfWindowSize;
  glm::vec2 center;
  float pixelsPerMeter;
  
  glm::vec2 pixelsPerMeterPos() const;
};

#endif
