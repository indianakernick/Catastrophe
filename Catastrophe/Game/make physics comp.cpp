//
//  make physics comp.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "make physics comp.hpp"

#include "player physics component.hpp"
#include "simple physics component.hpp"
#include <Simpleton/Utils/type list.hpp>
#include "oscillating physics component.hpp"
#include "../Libraries/Box2D/Dynamics/b2Body.h"

using PhysicsComps = Utils::TypeList<
  PlayerPhysicsComponent,
  SimplePhysicsComponent,
  OscillatingPhysicsComponent
>;

std::shared_ptr<PhysicsComponent> makePhysicsComp(
  const std::experimental::string_view name,
  const YAML::Node &node,
  const YAML::Node &level,
  b2World *const world
) {
  try {
    return Utils::getValueByName<
      std::shared_ptr<PhysicsComponent>,
      PhysicsComps
    >(name, [&node, &level, world] (auto t) {
      return std::make_shared<UTILS_TYPE(t)>(node, level, world);
    });
  } catch (Utils::TypeNotFound &) {
    throw std::runtime_error("Invalid physics component name");
  }
}
