//
//  spawn component list.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef spawn_component_list_hpp
#define spawn_component_list_hpp

#include "periodic spawn component.hpp"
#include <Simpleton/Type List/type.hpp>
#include "destroyable spawn component.hpp"
#include "droid shoot spawn component.hpp"
#include "player shoot spawn component.hpp"

using SpawnComps = List::Type<
  DestroyableSpawnComponent,
  PeriodicSpawnComponent,
  DroidShootSpawnComponent,
  PlayerShootSpawnComponent
>;

#endif
