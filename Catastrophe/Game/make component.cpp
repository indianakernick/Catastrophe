//
//  make component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "make component.hpp"

#include "components.hpp"
#include "ai component list.hpp"
#include "input component list.hpp"
#include "spawn component list.hpp"
#include <Simpleton/Utils/tuple.hpp>
#include "physics component list.hpp"
#include "particle component list.hpp"
#include "tracking component list.hpp"
#include "animation component list.hpp"
#include "rendering component list.hpp"

#define COMPONENT(NAME, I) NAME##Comps,
#define LAST_COMPONENT(NAME, I) NAME##Comps
using AllComps = Utils::TypeList<
  COMPONENTS
>;
#undef LAST_COMPONENT
#undef COMPONENT

template <typename List, typename Comp>
std::shared_ptr<Comp> makeComp(const std::string_view name) {
  try {
    return Utils::getValueByName<std::shared_ptr<Comp>, List>(name, [](auto t) {
      return std::make_shared<UTILS_TYPE(t)>();
    });
  } catch (Utils::TypeNotFound &) {
    throw std::runtime_error("Invalid component name");
  }
}

template <typename Comp>
std::shared_ptr<Comp> makeComp(const std::string_view name) {
  return makeComp<
    Utils::AtIndex<AllComps, COMPONENT_ID<Comp>>,
    Comp
  >(name);
}

#define COMPONENT(NAME, I)                                                         \
  template std::shared_ptr<NAME##Component> makeComp(std::string_view);
#define LAST_COMPONENT(NAME, I) COMPONENT(NAME, I)
COMPONENTS
#undef LAST_COMPONENT
#undef COMPONENT

namespace {
  int checkComponents() {
    Utils::forEachIndex<Utils::listSize<AllComps>>([] (auto i) {
      constexpr size_t index = UTILS_VALUE(i);
      using BaseComp = Utils::AtIndex<ComponentList, index>;
      static_assert(std::is_same_v<BaseComp, typename BaseComp::ComponentBase>);
      static_assert(std::is_abstract_v<BaseComp>);
      static_assert(std::is_base_of_v<Component, BaseComp>);
      static_assert(Utils::indexOf<ComponentList, BaseComp> == index);
      
      using CompList = Utils::AtIndex<AllComps, index>;
      Utils::forEach<CompList>([] (auto t) {
        using Comp = UTILS_TYPE(t);
        static_assert(std::is_base_of_v<BaseComp, Comp>);
        static_assert(!std::is_abstract_v<Comp>);//not necessarily final
      });
    });
    
    return 0;
  }
  
  const int dummy = checkComponents();
}
