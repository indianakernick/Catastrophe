//
//  camera.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 30/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef camera_hpp
#define camera_hpp

#include "rect.hpp"

int sizeToPixels(float);
glm::ivec2 sizeToPixels(glm::vec2);
glm::ivec2 sizeToPixels(float, float);

glm::ivec2 posToPixels(glm::vec2);
glm::ivec2 posToPixels(float, float);

RectPx rectToPixels(Rect);
  
float sizeToMeters(int);
glm::vec2 sizeToMeters(glm::ivec2);
glm::vec2 sizeToMeters(int, int);

glm::vec2 posToMeters(glm::ivec2);
glm::vec2 posToMeters(int, int);

Rect rectToMeters(RectPx);

#endif
