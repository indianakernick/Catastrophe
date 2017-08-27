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

class CameraToMeters {
public:
  CameraToMeters(glm::vec2, glm::vec2, float);
  
  float size(int) const;
  glm::vec2 size(glm::ivec2) const;
  glm::vec2 size(int, int) const;

  glm::vec2 pos(glm::ivec2) const;
  glm::vec2 pos(int, int) const;
  
  Rect rect(RectPx) const;
  
private:
  glm::vec2 halfWindowSize;
  glm::vec2 center;
  float pixelsPerMeter;
  
  glm::vec2 pixelsPerMeterPos() const;
};

#endif
