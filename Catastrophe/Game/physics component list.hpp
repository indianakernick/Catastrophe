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
#include "bullet physics component.hpp"
#include "missile physics component.hpp"
#include <Simpleton/Type List/type.hpp>
#include "launcher physics component.hpp"
#include "oscillating physics component.hpp"
#include "ground droid physics component.hpp"

using PhysicsComps = List::Type<
  PlayerPhysicsComponent,
  BodyPhysicsComponent,
  OscillatingPhysicsComponent,
  JointPhysicsComponent,
  ButtonPhysicsComponent,
  LauncherPhysicsComponent,
  MissilePhysicsComponent,
  TurretPhysicsComponent,
  GroundDroidPhysicsComponent,
  BulletPhysicsComponent
>;

#endif
