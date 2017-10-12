//
//  rendering component list.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef rendering_component_list_hpp
#define rendering_component_list_hpp

#include "spikes render component.hpp"
#include "player render component.hpp"
#include "polygon render component.hpp"
#include "missile render component.hpp"
#include "launcher render component.hpp"
#include "platform render component.hpp"
#include <Simpleton/Utils/type list.hpp>
#include "ground drone render component.hpp"
#include "vector sprite render component.hpp"
#include "spinning blade render component.hpp"
#include "missile spawner render component.hpp"

using RenderComps = Utils::TypeList<
  PolygonRenderComponent,
  LauncherRenderComponent,
  SpikesRenderComponent,
  PlatformRenderComponent,
  SpinningBladeRenderComponent,
  PlayerRenderComponent,
  VectorSpriteRenderComponent,
  GroundDroneRenderComponent,
  MissileRenderComponent,
  MissileSpawnerRenderComponent
>;

#endif
