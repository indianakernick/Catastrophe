//
//  make anim comp.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef make_anim_comp_hpp
#define make_anim_comp_hpp

#include <memory>
#include "transform.hpp"
#include <yaml-cpp/node/node.h>
#include "animation component.hpp"
#include <experimental/string_view>

std::shared_ptr<AnimationComponent> makeAnimComp(
  std::experimental::string_view,
  Entity *,
  const Sprite &,
  Transform,
  const YAML::Node &
);

#endif
