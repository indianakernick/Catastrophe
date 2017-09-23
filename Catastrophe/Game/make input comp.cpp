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
  Entity *const entity,
  const YAML::Node &args
) {
  try {
    return Utils::getValueByName<
      std::shared_ptr<InputComponent>,
      InputComps
    >(name, [entity, &args] (auto t) {
      return std::make_shared<UTILS_TYPE(t)>(entity, args);
    });
  } catch (Utils::TypeNotFound &) {
    throw std::runtime_error("Invalid input component name");
  }
}
