//
//  make physics comp.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 16/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef make_physics_comp_hpp
#define make_physics_comp_hpp

#include <memory>
#include <yaml-cpp/node/node.h>
#include "physics component.hpp"
#include <experimental/string_view>

std::shared_ptr<PhysicsComponent> makePhysicsComp(
  std::experimental::string_view,
  const YAML::Node &,
  const YAML::Node &,
  PhysicsSystem &
);

#endif
