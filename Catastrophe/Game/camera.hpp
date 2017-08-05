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
#include <glm/vec2.hpp>

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
  
  //pixels to meters
  float sizeToMeters(int) const;
  glm::vec2 sizeToMeters(glm::ivec2) const;
  glm::vec2 sizeToMeters(int, int) const;

  glm::vec2 posToMeters(glm::ivec2) const;
  glm::vec2 posToMeters(int, int) const;
  
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

private:
  glm::vec2 center;
};

#endif
