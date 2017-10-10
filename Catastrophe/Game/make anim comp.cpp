//
//  make anim comp.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "make anim comp.hpp"

#include <Simpleton/Utils/type list.hpp>
#include "player animation component.hpp"
#include "simple animation component.hpp"
#include "launcher animation component.hpp"

using AnimComps = Utils::TypeList<
  PlayerAnimationComponent,
  SimpleAnimationComponent,
  LauncherAnimationComponent
>;

std::shared_ptr<AnimationComponent> makeAnimComp(const std::experimental::string_view name) {
  try {
    return Utils::getValueByName<
      std::shared_ptr<AnimationComponent>,
      AnimComps
    >(name, [] (auto t) {
      return std::make_shared<UTILS_TYPE(t)>();
    });
  } catch (Utils::TypeNotFound &) {
    throw std::runtime_error("Invalid animation component name");
  }
}
