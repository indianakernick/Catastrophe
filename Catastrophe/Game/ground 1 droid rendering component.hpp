//
//  ground 1 droid rendering component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 22/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef ground_1_droid_rendering_component_hpp
#define ground_1_droid_rendering_component_hpp

#include "basic rendering component.hpp"

class Ground1DroidRenderingComponent final : public BasicRenderingComponent {
public:
  Ground1DroidRenderingComponent() = default;
  
  void render(NVGcontext *) override;
};

#endif
