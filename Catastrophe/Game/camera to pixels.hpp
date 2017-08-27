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

class CameraToPixels {
public:
  CameraToPixels(glm::vec2, glm::vec2, float);
  
  int size(float) const;
  glm::ivec2 size(glm::vec2) const;
  glm::ivec2 size(float, float) const;

  glm::ivec2 pos(glm::vec2) const;
  glm::ivec2 pos(float, float) const;
  
  RectPx rect(Rect) const;
  
private:
  glm::vec2 halfWindowSize;
  glm::vec2 center;
  float pixelsPerMeter;
  
  glm::vec2 pixelsPerMeterPos() const;
};

#endif
