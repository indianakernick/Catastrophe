//
//  static sprite render component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef static_sprite_render_component_hpp
#define static_sprite_render_component_hpp

#include "rect.hpp"
#include "render component.hpp"

class StaticSpriteRenderComponent final : public RenderComponent {
public:
  StaticSpriteRenderComponent(const std::string &, float, float);
  ~StaticSpriteRenderComponent() = default;
  
  void update(Entity *, float) override;
  void render(RenderingContext &) override;

private:
  std::string sprite;
  glm::vec2 center;
  glm::vec2 size;
};

#endif
