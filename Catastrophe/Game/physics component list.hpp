//
//  physics component list.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef physics_component_list_hpp
#define physics_component_list_hpp

#include "joint physics component.hpp"
#include "player physics component.hpp"
#include "button physics component.hpp"
#include "turret physics component.hpp"
#include "missile physics component.hpp"
#include <Simpleton/Utils/type list.hpp>
#include "launcher physics component.hpp"
#include "oscillating physics component.hpp"

using PhysicsComps = Utils::TypeList<
  PlayerPhysicsComponent,
  BodyPhysicsComponent,
  OscillatingPhysicsComponent,
  JointPhysicsComponent,
  ButtonPhysicsComponent,
  LauncherPhysicsComponent,
  MissilePhysicsComponent,
  TurretPhysicsComponent
>;

#endif
