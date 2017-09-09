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

struct CameraProps;

class CameraPos {
public:
  CameraPos();

  glm::vec2 calcCenter(CameraProps, glm::vec2, float);
  
private:
  glm::vec2 vel;
  glm::vec2 lastTarget;
  
  bool shouldStop(glm::vec2, float) const;
  glm::vec2 getSteer(glm::vec2, float) const;
};

#endif
