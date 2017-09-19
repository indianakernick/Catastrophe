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
  SimplePhysicsComponent(Entity *, b2Body *);
  
  void preStep(float) override;
  void postStep() override;
};

#endif
