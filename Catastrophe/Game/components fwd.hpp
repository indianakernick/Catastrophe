//
//  components fwd.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 14/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef components_fwd_hpp
#define components_fwd_hpp

#include <memory>
#include "component names.hpp"
#include <Simpleton/Utils/type list.hpp>

#define COMPONENT(NAME, I) class NAME##Component;
#define LAST_COMPONENT(NAME, I) COMPONENT(NAME, I)
COMPONENTS
#undef LAST_COMPONENT
#undef COMPONENT

#define COMPONENT(NAME, I) NAME##Component,
#define LAST_COMPONENT(NAME, I) NAME##Component
using ComponentList = Utils::TypeList<
  COMPONENTS
>;
#undef LAST_COMPONENT
#undef COMPONENT

template <typename Comp>
struct SmartPointer {
  using type = std::shared_ptr<Comp>;
};

using ComponentTuple = Utils::ListToTuple<Utils::TransformList<ComponentList, SmartPointer>>;

template <typename Comp>
constexpr size_t COMPONENT_ID = Utils::indexOf<ComponentList, Comp>;

#endif
