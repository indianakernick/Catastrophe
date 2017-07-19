//
//  component storage.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 18/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef component_storage_hpp
#define component_storage_hpp

#include <vector>
#include "settings.hpp"

template <typename Settings>
class ComponentStorage {
public:
  static_assert(IsSettings<Settings>::value);

  template <typename ...Comps>
  using TupleOfVector = std::tuple<std::vector<Comps>...>;
  
  using Components = Utils::UnpackInto<typename Settings::Comps, TupleOfVector>;
  using CompIndex = size_t;
  
  ComponentStorage() {
    growTo(100);
  }
  
  void growTo(const size_t newSize) {
    Utils::forEach(components, [newSize] (auto vector) {
      vector.resize(newSize);
    });
  }
  
  template <typename Comp>
  Comp &getComponent(const CompIndex index) {
    static_assert(Settings::template isComp<Comp>::value);
    assert(index < std::get<std::vector<Comp>>(components).size());
    return std::get<std::vector<Comp>>()[index];
  }
  
  Components components;
};

#endif
