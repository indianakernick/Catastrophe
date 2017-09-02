//
//  vector render.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 2/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef vector_render_hpp
#define vector_render_hpp

#include <experimental/string_view>
#include <glm/vec2.hpp>

struct Sprite;
class RenderingContext;

void renderSprite(
  RenderingContext &,
  const Sprite &,
  std::experimental::string_view,
  float,
  bool,
  glm::vec2,
  glm::vec2
);

#endif
