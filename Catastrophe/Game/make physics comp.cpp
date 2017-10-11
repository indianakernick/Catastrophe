//
//  make physics comp.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "make physics comp.hpp"

#include "joint physics component.hpp"
#include "player physics component.hpp"
#include "button physics component.hpp"
#include "missile physics component.hpp"
#include <Simpleton/Utils/type list.hpp>
#include "launcher physics component.hpp"
#include "oscillating physics component.hpp"
#include "../Libraries/Box2D/Dynamics/b2Body.h"

using PhysicsComps = Utils::TypeList<
  PlayerPhysicsComponent,
  BodyPhysicsComponent,
  OscillatingPhysicsComponent,
  JointPhysicsComponent,
  ButtonPhysicsComponent,
  LauncherPhysicsComponent,
  MissilePhysicsComponent
>;

std::shared_ptr<PhysicsComponent> makePhysicsComp(const std::experimental::string_view name) {
  try {
    return Utils::getValueByName<
      std::shared_ptr<PhysicsComponent>,
      PhysicsComps
    >(name, [] (auto t) {
      return std::make_shared<UTILS_TYPE(t)>();
    });
  } catch (Utils::TypeNotFound &) {
    throw std::runtime_error("Invalid physics component name");
  }
}
