//
//  ground 0 droid rendering component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef ground_0_droid_rendering_component_hpp
#define ground_0_droid_rendering_component_hpp

#include "basic rendering component.hpp"

class Ground0DroidRenderingComponent final : public BasicRenderingComponent {
public:
  Ground0DroidRenderingComponent() = default;
  
  void render(NVGcontext *) override;
};

#endif
