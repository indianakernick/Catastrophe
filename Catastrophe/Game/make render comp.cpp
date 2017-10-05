//
//  make render comp.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "make render comp.hpp"

#include "vector render component.hpp"
#include <Simpleton/Utils/type list.hpp>

using RenderComps = Utils::TypeList<
  VectorRenderComponent
>;

std::shared_ptr<RenderComponent> makeRenderComp(
  const std::experimental::string_view name,
  const YAML::Node &node,
  const YAML::Node &level
) {
  try {
    return Utils::getValueByName<
      std::shared_ptr<RenderComponent>,
      RenderComps
    >(name, [&node, &level] (auto t) {
      return std::make_shared<UTILS_TYPE(t)>(node, level);
    });
  } catch (Utils::TypeNotFound &) {
    throw std::runtime_error("Invalid render component name");
  }
}
