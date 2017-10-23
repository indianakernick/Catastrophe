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

struct PosVel {
  glm::vec2 pos;
  glm::vec2 vel;
};

struct PosVelAcc {
  glm::vec2 pos;
  glm::vec2 vel;
  glm::vec2 acc;
};

PosVel applyAcc(PosVelAcc, float);
glm::vec2 clampLength(glm::vec2, float);

struct ArriveConst {
  ///The distance from the target that the agent will start slowing down
  float slowDist;
  ///The maximum speed the agent will reach while traveling
  float maxSpeed;
  ///The amount of time it takes to accelerate to the desired velocity
  float timeToAcc;
};

glm::vec2 arrive(ArriveConst, PosVel, glm::vec2);

struct SeekConst {
  ///The maximum speed the agent will reach while traveling
  float maxSpeed;
  ///The amount of time it takes to accelerate to the desired velocity
  float timeToAcc;
};

glm::vec2 seek(SeekConst, PosVel, glm::vec2);

#endif
