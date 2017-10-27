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

glm::vec2 applyAcc(const glm::vec2 acc, const glm::vec2 vel, const float delta) {
  return acc * delta + vel;
}

glm::vec2 applySteer(const glm::vec2 agent, const glm::vec2 desired, const float time) {
  return (desired - agent) / time;
}

glm::vec2 clampLength(const glm::vec2 vec, const float maxLength) {
  const float vecLength = glm::length(vec);
  return vec / vecLength * std::min(vecLength, maxLength);
}

glm::vec2 arrive(
  const ArriveConst c,
  const glm::vec2 agent,
  const glm::vec2 target
) {
  const glm::vec2 targetDir = target - agent;
  const float targetDist = glm::length(targetDir);
  const float desiredSpeed = std::min(targetDist, c.slowDist) / c.slowDist * c.maxSpeed;
  return targetDir / targetDist * desiredSpeed;
}

glm::vec2 seek(
  const SeekConst c,
  const glm::vec2 agent,
  const glm::vec2 target
) {
  return glm::normalize(target - agent) * c.maxSpeed;
}

glm::vec2 flee(
  const FleeConst c,
  const glm::vec2 agent,
  const glm::vec2 target
) {
  return glm::normalize(agent - target) * c.maxSpeed;
}
