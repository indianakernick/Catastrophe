//
//  player visible component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef player_visible_component_hpp
#define player_visible_component_hpp

#include "rect.hpp"
#include "visible component.hpp"

class PlayerVisibleComponent : public VisibleComponent {
public:
  PlayerVisibleComponent() = default;
  ~PlayerVisibleComponent() = default;
  
  void update(Entity *, float) override;
  void render(RenderingContext &) override;

private:
  Rect rect;
};

#endif
