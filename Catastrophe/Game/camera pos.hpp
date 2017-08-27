//
//  camera pos.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 27/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef camera_pos_hpp
#define camera_pos_hpp

#include <glm/vec2.hpp>

class CameraPos {

  friend class Camera;

public:
  CameraPos();
  
  //call set to move to a positon
  void set(glm::vec2);
  //repeatedly call setMoving to follow a moving target
  void setMoving(glm::vec2);
  glm::vec2 get() const;
  
private:
  glm::vec2 center;
  glm::vec2 motionVel;
  glm::vec2 motionTarget;
  glm::vec2 lastMotionTarget;
  
  void animate(float);
};

#endif
