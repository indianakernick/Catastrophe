//
//  vector render.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 4/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef vector_render_hpp
#define vector_render_hpp

#include <glm/mat3x3.hpp>
#include <experimental/string_view>

struct Sprite;
extern "C" struct NVGcontext;

void renderSprite(
  NVGcontext *,
  const Sprite &,
  std::experimental::string_view,
  const glm::mat3 &,
  float
);

#endif
