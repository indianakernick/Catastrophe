//
//  transform.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef transform_hpp
#define transform_hpp

#include <glm/vec2.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>

struct Transform {
  Transform();
  explicit Transform(glm::vec2);
  Transform(glm::vec2, glm::vec2, float = 0.0f);

  glm::mat2 getMat2() const;
  glm::mat3 getMat3() const;

  glm::vec2 pos;
  glm::vec2 scale;
  float rotation;
};

#endif
