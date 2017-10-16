//
//  matrix mul.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 16/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef matrix_mul_hpp
#define matrix_mul_hpp

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>

inline glm::vec2 mul(const glm::mat2 &mat, const glm::vec2 vec) {
  return mat * vec;
}

inline glm::vec2 mulPos(const glm::mat3 &mat, const glm::vec2 pos) {
  return mat * glm::vec3(pos.x, pos.y, 1.0f);
}

inline glm::vec2 mulVec(const glm::mat3 &mat, const glm::vec2 vec) {
  return mat * glm::vec3(vec.x, vec.y, 0.0f);
}

inline float mulScalar(const glm::mat2 &mat, const float scalar) {
  //nvg__getAverageScale
  //See nvgTransform in "nvg helper.hpp" for the conversion between
  //nvg matricies and glm matricies
  
  auto square = [] (const float n) {
    return n * n;
  };
  
  const float sx = std::sqrt(square(mat[0][0]) + square(mat[1][0]));
  const float sy = std::sqrt(square(mat[0][1]) + square(mat[1][1]));
  return scalar * (sx + sy) * 0.5f;
}

inline float mulScalar(const glm::mat3 &mat, const float scalar) {
  return mulScalar(static_cast<glm::mat2>(mat), scalar);
}

#endif
