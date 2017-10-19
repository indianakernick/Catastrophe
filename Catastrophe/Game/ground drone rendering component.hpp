//
//  ground drone rendering component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 11/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef ground_drone_rendering_component_hpp
#define ground_drone_rendering_component_hpp

#include "nanovg.hpp"
#include "basic rendering component.hpp"

class GroundDroneRenderingComponent final : public BasicRenderingComponent {
public:
  GroundDroneRenderingComponent() = default;
  
  void render(NVGcontext *) override;

private:
  static const NVGcolor OUTLINE;
  static const NVGcolor FILL;
};

#endif
