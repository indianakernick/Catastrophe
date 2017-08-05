//
//  static color render component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef static_color_render_component_hpp
#define static_color_render_component_hpp

#include "color.hpp"
#include <glm/vec2.hpp>
#include "render component.hpp"

class StaticColorRenderComponent final : public RenderComponent {
public:
  StaticColorRenderComponent(Color, float, float);
  ~StaticColorRenderComponent() = default;
  
  void update(Entity *, float) override;
  void render(RenderingContext &) override;
  
private:
  Color color;
  glm::vec2 center;
  glm::vec2 size;
};

#endif
