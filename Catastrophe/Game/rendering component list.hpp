//
//  rendering component list.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef rendering_component_list_hpp
#define rendering_component_list_hpp

#include <Simpleton/Utils/type list.hpp>
#include "spikes rendering component.hpp"
#include "player rendering component.hpp"
#include "polygon rendering component.hpp"
#include "missile rendering component.hpp"
#include "launcher rendering component.hpp"
#include "platform rendering component.hpp"
#include "ground drone rendering component.hpp"
#include "vector sprite rendering component.hpp"
#include "spinning blade rendering component.hpp"
#include "ground 0 droid rendering component.hpp"
#include "missile spawner rendering component.hpp"

using RenderingComps = Utils::TypeList<
  PolygonRenderingComponent,
  LauncherRenderingComponent,
  SpikesRenderingComponent,
  PlatformRenderingComponent,
  SpinningBladeRenderingComponent,
  PlayerRenderingComponent,
  VectorSpriteRenderingComponent,
  GroundDroneRenderingComponent,
  MissileRenderingComponent,
  MissileSpawnerRenderingComponent,
  Ground0DroidRenderingComponent
>;

#endif
