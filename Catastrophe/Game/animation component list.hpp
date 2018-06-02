//
//  animation component list.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef animation_component_list_hpp
#define animation_component_list_hpp

#include <Simpleton/Type List/type.hpp>
#include "player animation component.hpp"
#include "simple animation component.hpp"
#include "turret animation component.hpp"
#include "launcher animation component.hpp"
#include "ground droid animation component.hpp"

using AnimationComps = List::Type<
  PlayerAnimationComponent,
  SimpleAnimationComponent,
  LauncherAnimationComponent,
  TurretAnimationComponent,
  GroundDroidAnimationComponent
>;

#endif
