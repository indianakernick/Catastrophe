//
//  velocity direction.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "velocity direction.hpp"

#include <cmath>

VelDir1::VelDir1(const float lastDir)
  : lastDir(lastDir) {}

float VelDir1::getDir(const float vel) {
  if (std::abs(vel) < 0.01f) {
    return lastDir;
  } else if (vel < 0.0f) {
    return lastDir = -1.0f;
  } else {
    return lastDir = 1.0f;
  }
}

float VelDir1::getDir() const {
  return lastDir;
}

VelDir2::VelDir2(const glm::vec2 lastDir)
  : x(lastDir.x), y(lastDir.y) {}

glm::vec2 VelDir2::getDir(const glm::vec2 vel) {
  return {
    x.getDir(vel.x),
    y.getDir(vel.y)
  };
}

glm::vec2 VelDir2::getDir() const {
  return {
    x.getDir(),
    y.getDir()
  };
}
