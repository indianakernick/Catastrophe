//
//  missile physics component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef missile_physics_component_hpp
#define missile_physics_component_hpp

#include "physics component.hpp"

class MissilePhysicsComponent final : public PhysicsComponent {
public:
  MissilePhysicsComponent() = default;
  
  void init(b2World &, const YAML::Node &) override;
  void preStep(float) override;
  void postStep() override;
  
  void beginContact();

private:
  float moveSpeed = 0.5f;
  bool contacted = false;
};

#endif
