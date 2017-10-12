//
//  animation component list.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef animation_component_list_hpp
#define animation_component_list_hpp

#include <Simpleton/Utils/type list.hpp>
#include "player animation component.hpp"
#include "simple animation component.hpp"
#include "launcher animation component.hpp"

using AnimationComps = Utils::TypeList<
  PlayerAnimationComponent,
  SimpleAnimationComponent,
  LauncherAnimationComponent
>;

#endif
