//
//  velocity direction.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef velocity_direction_hpp
#define velocity_direction_hpp

#include <glm/vec2.hpp>

class VelDir1 {
public:
  VelDir1() = default;
  explicit VelDir1(float);
  
  float getDir(float);
  float getDir() const;

private:
  float lastDir = 1.0f;
};

class VelDir2 {
public:
  VelDir2() = default;
  explicit VelDir2(const glm::vec2);
  
  glm::vec2 getDir(glm::vec2);
  glm::vec2 getDir() const;

private:
  VelDir1 x;
  VelDir1 y;
};

#endif
