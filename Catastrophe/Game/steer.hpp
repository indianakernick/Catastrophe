//
//  steer.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 23/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef steer_hpp
#define steer_hpp

#include <glm/vec2.hpp>

glm::vec2 applyAcc(glm::vec2, glm::vec2, float);
glm::vec2 applySteer(glm::vec2, glm::vec2, float);

struct ArriveConst {
  ///The distance from the target that the agent will start slowing down
  float slowDist;
  ///The maximum speed the agent will reach while traveling
  float maxSpeed;
};

glm::vec2 arrive(ArriveConst, glm::vec2, glm::vec2);

struct SeekConst {
  ///The maximum speed the agent will reach while traveling
  float maxSpeed;
};

glm::vec2 seek(SeekConst, glm::vec2, glm::vec2);

using FleeConst = SeekConst;

glm::vec2 flee(FleeConst, glm::vec2, glm::vec2);

#endif
