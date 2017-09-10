//
//  simple physics component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 3/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef simple_physics_component_hpp
#define simple_physics_component_hpp

#include "physics component.hpp"

class SimplePhysicsComponent final : public PhysicsComponent {
public:
  explicit SimplePhysicsComponent(b2Body *);
  
  void preStep(PhysicsState &, const InputCommands &, float) override;
  void postStep(PhysicsState &, const InputCommands &) override;
};

#endif
