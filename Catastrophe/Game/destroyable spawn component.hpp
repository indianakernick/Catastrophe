//
//  destroyable spawn component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef destroyable_spawn_component_hpp
#define destroyable_spawn_component_hpp

#include "spawn component.hpp"

class DestroyableSpawnComponent final : public SpawnComponent {
public:
  DestroyableSpawnComponent() = default;
  
  void init(const YAML::Node &) override;
  void update(float) override;
  
  bool shouldDestroySelf() const override;

  void kill();
  
private:
  bool dead = false;
};

#endif
