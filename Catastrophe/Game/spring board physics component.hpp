//
//  spring board physics component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 4/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef spring_board_physics_component_hpp
#define spring_board_physics_component_hpp

#include <yaml-cpp/node/node.h>
#include "physics component.hpp"

class SpringBoardPhysicsComponent final : public PhysicsComponent {
public:
  SpringBoardPhysicsComponent(const YAML::Node &, const YAML::Node &, PhysicsSystem &);
  
  void preStep(float) override;
  void postStep() override;
};

#endif
