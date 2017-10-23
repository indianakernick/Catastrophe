//
//  steer.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 23/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "steer.hpp"

#include <cmath>
#include <algorithm>
#include <glm/gtx/norm.hpp>

PosVel applyAcc(const PosVelAcc in, const float delta) {
  PosVel out;
  out.vel = in.vel + in.acc * delta;
  out.pos = in.pos + out.vel * delta;
  return out;
}

glm::vec2 clampLength(const glm::vec2 vec, const float maxLength) {
  const float vecLength = glm::length(vec);
  return vec / vecLength * std::min(vecLength, maxLength);
}

glm::vec2 arrive(
  const ArriveConst c,
  const PosVel agent,
  const glm::vec2 target
) {
  const glm::vec2 targetDir = target - agent.pos;
  const float targetDist = glm::length(targetDir);
  
  const float desiredSpeed = std::min(targetDist, c.slowDist) / c.slowDist * c.maxSpeed;
  const glm::vec2 desiredVel = targetDir / targetDist * desiredSpeed;
  
  return (desiredVel - agent.vel) / c.timeToAcc;
}

glm::vec2 seek(
  const SeekConst c,
  const PosVel agent,
  const glm::vec2 target
) {
  const glm::vec2 targetDir = target - agent.pos;
  const glm::vec2 desiredVel = glm::normalize(targetDir) * c.maxSpeed;
  return (desiredVel - agent.vel) / c.timeToAcc;
}
