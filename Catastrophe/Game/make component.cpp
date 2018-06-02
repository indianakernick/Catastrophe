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
#include <Simpleton/Type List/get.hpp>
#include "animation component list.hpp"
#include "rendering component list.hpp"

#define COMPONENT(NAME, I) NAME##Comps,
#define LAST_COMPONENT(NAME, I) NAME##Comps
using AllComps = List::Type<
  COMPONENTS
>;
#undef LAST_COMPONENT
#undef COMPONENT

template <typename CompList, typename Comp>
std::shared_ptr<Comp> makeComp(const std::string_view name) {
  try {
    return List::getValueByName<std::shared_ptr<Comp>, CompList>(name, [](auto t) {
      return std::make_shared<LIST_TYPE(t)>();
    });
  } catch (List::TypeNotFound &) {
    throw std::runtime_error("Invalid component name");
  }
}

template <typename Comp>
std::shared_ptr<Comp> makeComp(const std::string_view name) {
  return makeComp<
    List::AtIndex<AllComps, COMPONENT_ID<Comp>>,
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
    Utils::forEachIndex<List::Size<AllComps>>([] (auto i) {
      constexpr size_t index = UTILS_VALUE(i);
      using BaseComp = List::AtIndex<ComponentList, index>;
      static_assert(std::is_same_v<BaseComp, typename BaseComp::ComponentBase>);
      static_assert(std::is_abstract_v<BaseComp>);
      static_assert(std::is_base_of_v<Component, BaseComp>);
      static_assert(List::IndexOf<ComponentList, BaseComp> == index);
      
      using CompList = List::AtIndex<AllComps, index>;
      List::forEach<CompList>([] (auto t) {
        using Comp = LIST_TYPE(t);
        static_assert(std::is_base_of_v<BaseComp, Comp>);
        static_assert(!std::is_abstract_v<Comp>);//not necessarily final
      });
    });
    
    return 0;
  }
  
  const int dummy = checkComponents();
}
