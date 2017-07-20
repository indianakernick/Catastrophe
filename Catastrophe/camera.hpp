//
//  camera.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 20/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef camera_hpp
#define camera_hpp

#include "rect.hpp"
#include <glm/vec2.hpp>
#include <Simpleton/Time/delta anim.hpp>

class Camera {
public:
  Camera() = default;
  explicit Camera(glm::vec2);
  ~Camera() = default;
  
  void update(float);
  
  void moveTo(glm::vec2);
  void moveInTime(glm::vec2, float);
  
  RectPx transform(Rect) const;

private:
  glm::vec2 currPos;
  glm::vec2 nextPos;
  Time::DeltaAnim anim;
  
  glm::vec2 getPos() const;
};

#endif
