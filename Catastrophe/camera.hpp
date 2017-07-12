//
//  camera.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef camera_hpp
#define camera_hpp

#include "rect.hpp"

class Camera {
public:
  Camera() = default;
  explicit Camera(glm::vec2);
  ~Camera() = default;

  void setPos(glm::vec2);
  glm::vec2 getSize() const;
  
  RectPx transform(Rect) const;

private:
  static constexpr float PIXELS_PER_TILE = 16.0f;

  glm::vec2 pos;
};

#endif
