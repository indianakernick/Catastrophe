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
  Entity *const entity,
  b2Body *const body,
  const YAML::Node &args
) {
  try {
    return Utils::getValueByName<
      std::shared_ptr<PhysicsComponent>,
      PhysicsComps
    >(name, [entity, body, args] (auto t) {
      auto component = std::make_shared<UTILS_TYPE(t)>(entity, body, args);
      body->SetUserData(component.get());
      return component;
    });
  } catch (Utils::TypeNotFound &) {
    throw std::runtime_error("Invalid physics component name");
  }
}
