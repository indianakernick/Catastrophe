//
//  missile physics component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef missile_physics_component_hpp
#define missile_physics_component_hpp

#include "body physics component.hpp"

class MissilePhysicsComponent final : public BodyPhysicsComponent {
public:
  MissilePhysicsComponent() = default;
  
  void preStep(float) override;
  void postStep() override;
  
  void beginContact();

private:
  bool contacted = false;
};

#endif
