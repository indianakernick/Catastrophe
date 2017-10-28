//
//  player bullet rendering component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef player_bullet_rendering_component_hpp
#define player_bullet_rendering_component_hpp

#include "basic rendering component.hpp"

class PlayerBulletRenderingComponent final : public BasicRenderingComponent {
public:
  PlayerBulletRenderingComponent() = default;
  
  void render(NVGcontext *) override;
};

#endif
