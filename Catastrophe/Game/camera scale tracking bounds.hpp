//
//  camera scale tracking bounds.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 27/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef camera_scale_tracking_bounds_hpp
#define camera_scale_tracking_bounds_hpp

#include <glm/vec2.hpp>

class CameraScaleTrackingBounds {
public:
  CameraScaleTrackingBounds(glm::vec2, glm::vec2, float);
  
  glm::vec2 centerToMeters(glm::vec2) const;
  glm::vec2 sizeToMeters(glm::vec2) const;
  
private:
  glm::vec2 windowSize;
  glm::vec2 center;
  float pixelsPerMeter;
  
  glm::vec2 toMeters(glm::vec2) const;
};

#endif
