//
//  camera transform.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 3/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef camera_transform_hpp
#define camera_transform_hpp

#include "rect.hpp"
#include <glm/mat3x3.hpp>

struct CameraProps;

glm::mat3 toPixels(CameraProps);
glm::mat3 toMeters(CameraProps);

glm::vec2 mulPoint(const glm::mat3 &, glm::vec2);
glm::vec2 mulSize(const glm::mat3 &, glm::vec2);
float mulSize(const glm::mat3 &, float);

RectPx mulRect(const glm::mat3 &, Rect);
Rect mulRectPx(const glm::mat3 &, RectPx);

std::pair<glm::vec2, float> mulCircle(const glm::mat3 &, glm::vec2, float);
std::pair<glm::vec2, glm::vec2> mulLine(const glm::mat3 &, glm::vec2, glm::vec2);

#endif
