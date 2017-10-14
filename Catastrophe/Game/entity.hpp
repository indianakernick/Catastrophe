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
#include "components fwd.hpp"

class Entity {
public:
  explicit Entity(EntityID);
  
  template <typename Comp>
  std::shared_ptr<Comp> get() {
    return std::get<COMPONENT_ID<Comp>>(components);
  }
  template <typename Comp>
  std::shared_ptr<const Comp> get() const {
    return std::get<COMPONENT_ID<Comp>>(components);
  }
  template <typename Comp>
  void set(const std::shared_ptr<Comp> comp) {
    std::get<COMPONENT_ID<Comp>>(components) = comp;
  }
  
  template <typename Comp>
  std::shared_ptr<Comp> getImpl() {
    using Base = typename Comp::ComponentBase;
    return std::dynamic_pointer_cast<Comp>(
      std::get<COMPONENT_ID<Base>>(components)
    );
  }
  template <typename Comp>
  std::shared_ptr<const Comp> getImpl() const {
    using Base = typename Comp::ComponentBase;
    return std::dynamic_pointer_cast<const Comp>(
      std::get<COMPONENT_ID<Base>>(components)
    );
  }
  
  EntityID getID() const;

private:
  ComponentTuple components;
  EntityID id;
};

#endif
