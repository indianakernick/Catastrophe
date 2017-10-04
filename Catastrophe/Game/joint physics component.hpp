//
//  joint physics component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 4/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef joint_physics_component_hpp
#define joint_physics_component_hpp

#include <yaml-cpp/node/node.h>
#include "physics component.hpp"

class JointPhysicsComponent final : public PhysicsComponent {
public:
  JointPhysicsComponent(const YAML::Node &, const YAML::Node &, PhysicsSystem &);
  
  void preStep(float) override;
  void postStep() override;
};

#endif
