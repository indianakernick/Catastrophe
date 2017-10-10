//
//  make render comp.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "make render comp.hpp"

#include "spikes render component.hpp"
#include "player render component.hpp"
#include "polygon render component.hpp"
#include "launcher render component.hpp"
#include "platform render component.hpp"
#include <Simpleton/Utils/type list.hpp>
#include "vector sprite render component.hpp"
#include "spinning blade render component.hpp"

using RenderComps = Utils::TypeList<
  PolygonRenderComponent,
  LauncherRenderComponent,
  SpikesRenderComponent,
  PlatformRenderComponent,
  SpinningBladeRenderComponent,
  PlayerRenderComponent,
  VectorSpriteRenderComponent
>;

std::shared_ptr<RenderComponent> makeRenderComp(const std::experimental::string_view name) {
  try {
    return Utils::getValueByName<
      std::shared_ptr<RenderComponent>,
      RenderComps
    >(name, [] (auto t) {
      return std::make_shared<UTILS_TYPE(t)>();
    });
  } catch (Utils::TypeNotFound &) {
    throw std::runtime_error("Invalid render component name");
  }
}
