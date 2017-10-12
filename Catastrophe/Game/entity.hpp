//
//  entity.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef entity_hpp
#define entity_hpp

#include <memory>
#include "entity id.hpp"
#include "components.hpp"

class Entity {
public:
  explicit Entity(EntityID);
  
  template <typename Comp>
  auto &get() {
    return std::get<COMPONENT_ID<Comp>>(components);
  }
  template <typename Comp>
  const auto &get() const {
    return std::get<COMPONENT_ID<Comp>>(components);
  }
  template <typename Comp>
  void set(const std::shared_ptr<Comp> comp) {
    std::get<COMPONENT_ID<Comp>>(components) = comp;
  }
  EntityID getID() const;

private:
  ComponentTuple components;
  EntityID id;
};

#endif
