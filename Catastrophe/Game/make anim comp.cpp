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
#include "static animation component.hpp"

using AnimComps = Utils::TypeList<
  PlayerAnimationComponent,
  StaticAnimationComponent
>;

std::shared_ptr<AnimationComponent> makeAnimComp(
  const std::experimental::string_view name,
  Entity *const entity,
  const Sprite &sprite,
  const Transform transform
) {
  try {
    return Utils::getValueByName<
      std::shared_ptr<AnimationComponent>,
      AnimComps
    >(name, [entity, sprite, transform] (auto t) {
      return std::make_shared<typename decltype(t)::type>(
        entity,
        sprite,
        transform
      );
    });
  } catch (Utils::TypeNotFound &) {
    throw std::runtime_error("Invalid animation component name");
  }
}
