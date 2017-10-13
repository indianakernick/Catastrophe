//
//  camera transform.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 13/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef camera_transform_hpp
#define camera_transform_hpp

#include "aabb.hpp"
#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>

struct CameraProps;

class CameraTransform {
public:
  CameraTransform() = default;
  
  glm::mat3 toPixels() const;
  glm::mat3 toMeters() const;
  bool visibleMeters(AABB) const;
  
  void updateMatricies(CameraProps);
  
private:
  glm::mat3 toPixelsMat;
  glm::mat3 toMetersMat;
  AABB windowBounds;
};

#endif
