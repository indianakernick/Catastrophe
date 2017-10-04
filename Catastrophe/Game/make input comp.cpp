//
//  make input comp.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "make input comp.hpp"

#include "player input component.hpp"
#include <Simpleton/Utils/type list.hpp>

using InputComps = Utils::TypeList<
  PlayerInputComponent
>;

std::shared_ptr<InputComponent> makeInputComp(
  const std::experimental::string_view name,
  const YAML::Node &node,
  const YAML::Node &level
) {
  try {
    return Utils::getValueByName<
      std::shared_ptr<InputComponent>,
      InputComps
    >(name, [&node, &level] (auto t) {
      return std::make_shared<UTILS_TYPE(t)>(node, level);
    });
  } catch (Utils::TypeNotFound &) {
    throw std::runtime_error("Invalid input component name");
  }
}
