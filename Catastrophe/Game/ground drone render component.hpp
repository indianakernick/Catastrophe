//
//  ground drone render component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 11/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef ground_drone_render_component_hpp
#define ground_drone_render_component_hpp

#include "basic render component.hpp"

class GroundDroneRenderComponent final : public BasicRenderComponent {
public:
  GroundDroneRenderComponent() = default;
  
  void render(NVGcontext *) override;
};

#endif
