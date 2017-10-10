//
//  joint physics component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 4/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef joint_physics_component_hpp
#define joint_physics_component_hpp

#include "physics component.hpp"

class JointPhysicsComponent : public PhysicsComponent {
public:
  JointPhysicsComponent() = default;
  
  void init(b2World &, const YAML::Node &) override;
  void preStep(float) override;
  void postStep() override;
};

#endif
