//
//  missile spawner rendering component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef missile_spawner_rendering_component_hpp
#define missile_spawner_rendering_component_hpp

#include "basic rendering component.hpp"

class MissileSpawnerRenderingComponent final : public BasicRenderingComponent {
public:
  MissileSpawnerRenderingComponent() = default;
  
  void render(NVGcontext *) override;
  AABB getAABB() const override;
};

#endif
