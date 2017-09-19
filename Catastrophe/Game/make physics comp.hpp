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
#include "physics component.hpp"
#include "../Libraries/Box2D/Dynamics/b2Body.h"

template <typename Component>
std::shared_ptr<PhysicsComponent> makePhysicsComp(
  Entity *const entity,
  b2Body *const body
) {
  auto component = std::make_shared<Component>(entity, body);
  body->SetUserData(component.get());
  return component;
}

#endif
