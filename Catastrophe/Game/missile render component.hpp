//
//  missile render component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef missile_render_component_hpp
#define missile_render_component_hpp

#include "basic render component.hpp"

class MissileRenderComponent final : public BasicRenderComponent {
public:
  MissileRenderComponent() = default;
  
  void render(NVGcontext *) override;
};

#endif
