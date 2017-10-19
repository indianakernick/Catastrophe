//
//  player rendering component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef player_rendering_component_hpp
#define player_rendering_component_hpp

#include "basic rendering component.hpp"

class PlayerRenderingComponent final : public BasicRenderingComponent {
public:
  PlayerRenderingComponent() = default;
  
  void render(NVGcontext *) override;
};

#endif
