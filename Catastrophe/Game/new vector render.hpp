//
//  new vector render.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 4/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef new_vector_render_hpp
#define new_vector_render_hpp

#include <experimental/string_view>
#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>

struct Sprite;
extern "C" struct NVGcontext;

void newRenderSprite(
  NVGcontext *,
  const Sprite &,
  std::experimental::string_view,
  const glm::mat3 &,
  float,
  bool
);

#endif
