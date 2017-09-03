//
//  matrix mul.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 3/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef matrix_mul_hpp
#define matrix_mul_hpp

#include "rect.hpp"
#include <glm/mat3x3.hpp>

glm::vec2 mulPoint(const glm::mat3 &, glm::vec2);
glm::vec2 mulSize(const glm::mat3 &, glm::vec2);
float mulSize(const glm::mat3 &, float);

RectPx mulRect(const glm::mat3 &, Rect);
Rect mulRectPx(const glm::mat3 &, RectPx);

std::pair<glm::vec2, float> mulCircle(const glm::mat3 &, glm::vec2, float);
std::pair<glm::vec2, glm::vec2> mulLine(const glm::mat3 &, glm::vec2, glm::vec2);

#endif
