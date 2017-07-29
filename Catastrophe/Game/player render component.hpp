//
//  player render component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef player_render_component_hpp
#define player_render_component_hpp

#include "rect.hpp"
#include "render component.hpp"

class PlayerRenderComponent : public RenderComponent {
public:
  PlayerRenderComponent() = default;
  ~PlayerRenderComponent() = default;
  
  void update(Entity *, float) override;
  void render(RenderingContext &) override;

private:
  Rect rect;
};

#endif
