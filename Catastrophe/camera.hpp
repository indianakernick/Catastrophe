//
//  camera.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef camera_hpp
#define camera_hpp

#include <SDL2/SDL_rect.h>
#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>

class Camera {
public:
  void setPos(glm::vec2);
  
  SDL_Rect transform(glm::vec2, glm::vec2) const;

private:
  static constexpr float PIXELS_PER_TILE = 16.0f;

  glm::vec2 pos;
};

#endif
