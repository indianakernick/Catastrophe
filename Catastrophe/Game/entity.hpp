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
#include <Simpleton/Utils/type name.hpp>

class Entity {
public:
  explicit Entity(EntityID);
  
  template <typename Comp>
  void set(const std::shared_ptr<Comp> comp) {
    std::get<COMPONENT_ID<Comp>>(components) = comp;
  }
  
  template <typename Comp>
  std::shared_ptr<Comp> get() {
    return std::get<COMPONENT_ID<Comp>>(components);
  }
  template <typename Comp>
  std::shared_ptr<const std::remove_const_t<Comp>> get() const {
    return std::get<COMPONENT_ID<Comp>>(components);
  }
  
  template <typename Comp>
  auto getExpected() {
    return expect(get<Comp>());
  }
  
  template <typename Comp>
  auto getExpected() const {
    return expect(get<Comp>());
  }
  
  template <typename Comp>
  std::shared_ptr<Comp> getImpl() {
    using Base = typename Comp::ComponentBase;
    return std::dynamic_pointer_cast<Comp>(
      std::get<COMPONENT_ID<Base>>(components)
    );
  }
  template <typename Comp>
  std::shared_ptr<const std::remove_const_t<Comp>> getImpl() const {
    using Base = typename Comp::ComponentBase;
    return std::dynamic_pointer_cast<const Comp>(
      std::get<COMPONENT_ID<Base>>(components)
    );
  }
  
  template <typename Comp>
  auto getExpectedImpl() {
    return expect(getImpl<Comp>());
  }
  template <typename Comp>
  auto getExpectedImpl() const {
    return expect(getImpl<Comp>());
  }
  
  EntityID getID() const;

private:
  ComponentTuple components;
  EntityID id;
  
  template <typename Comp>
  std::shared_ptr<Comp> expect(const std::shared_ptr<Comp> comp) const {
    if (comp) {
      return comp;
    } else {
      throw std::runtime_error(
        "Expected entity to contain "
        + std::string(Utils::typeName<std::remove_cv_t<Comp>>())
      );
    }
  }
};

#endif
