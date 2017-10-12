//
//  make component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "make component.hpp"

#include "components.hpp"
#include "input component list.hpp"
#include "spawn component list.hpp"
#include "physics component list.hpp"
#include "animation component list.hpp"
#include "rendering component list.hpp"

#define COMPONENT(NAME) NAME##Comps,
#define LAST_COMPONENT(NAME) NAME##Comps
using AllComps = Utils::TypeList<
  COMPONENTS
>;
#undef LAST_COMPONENT
#undef COMPONENT

template <typename List, typename Comp>
std::shared_ptr<Comp> makeComp(const std::experimental::string_view name) {
  try {
    return Utils::getValueByName<std::shared_ptr<Comp>, List>(name, [](auto t) {
      return std::make_shared<UTILS_TYPE(t)>();
    });
  } catch (Utils::TypeNotFound &) {
    throw std::runtime_error("Invalid component name");
  }
}

template <typename Comp>
std::shared_ptr<Comp> makeComp(const std::experimental::string_view name) {
  return makeComp<
    Utils::AtIndex<AllComps, COMPONENT_ID<Comp>>,
    Comp
  >(name);
}

#define COMPONENT(NAME)                                                         \
  template std::shared_ptr<NAME##Component> makeComp(std::experimental::string_view);
#define LAST_COMPONENT(NAME) COMPONENT(NAME)
COMPONENTS
#undef LAST_COMPONENT
#undef COMPONENT
