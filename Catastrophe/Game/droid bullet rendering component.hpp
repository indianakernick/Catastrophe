//
//  droid bullet rendering component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 22/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef droid_bullet_rendering_component_hpp
#define droid_bullet_rendering_component_hpp

#include "basic rendering component.hpp"

class DroidBulletRenderingComponent final : public BasicRenderingComponent {
public:
  DroidBulletRenderingComponent() = default;
  
  void render(NVGcontext *) override;
};

#endif
