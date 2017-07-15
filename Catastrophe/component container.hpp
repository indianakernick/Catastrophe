//
//  component container.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 14/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef component_container_hpp
#define component_container_hpp

#include <vector>
#include <memory>
#include <Simpleton/ID/type.hpp>
#include <Simpleton/Utils/safe down cast.hpp>

///A generic container for components
template <
  typename Object,
  typename Component,
  Object *Component::*OBJECT_PTR = nullptr
>
class ComponentContainer {
private:
  template <typename Ret, typename Comp>
  using EnableIfComponent = std::enable_if_t<
    std::is_base_of<Component, Comp>::value &&
    !std::is_same<Component, Comp>::value,
    Ret
  >;
  
  template <typename Comp>
  using GetComponentID = ID::TypeCounter<size_t, Comp, Component>;

public:
  class BadObjectPtr final : public std::logic_error {
  public:
    explicit BadObjectPtr(const char *what)
      : std::logic_error(what) {}
  };
  
  class DuplicateComponent final : public std::logic_error {
  public:
    DuplicateComponent()
      : std::logic_error("Cannot add more than one component of the same type") {}
  };
  
  class NoComponent final : public std::logic_error {
  public:
    NoComponent()
      : std::logic_error("Tried to get a component that does not exist") {}
  };
  
  ComponentContainer() = default;
  ~ComponentContainer() {
    static_assert(std::is_base_of<ComponentContainer, Object>::value);
  }
  
  void swapComponents(ComponentContainer &other) {
    components.swap(other.components);
  }
  
  template <typename ...MethodArgs, typename ...Args>
  void updateComps(void (Component::*METHOD)(MethodArgs...), Args &... args) {
    for (auto c = components.cbegin(); c != components.cend(); ++c) {
      if (*c) {
        (*c)->*METHOD(args...);
      }
    }
  }
  
  template <typename Comp>
  EnableIfComponent<void, Comp> addComp(const std::shared_ptr<Comp> component) {
    if constexpr (OBJECT_PTR) {
      if (component->*OBJECT_PTR == static_cast<Object *>(this)) {
        throw BadObjectPtr("Cannot add component to same object twice");
      } else if (component->*OBJECT_PTR != nullptr) {
        throw BadObjectPtr("Cannot add component to more than one object");
      }
    }
    
    const size_t index = GetComponentID<Comp>::get();
    if (index < components.size()) {
      if (components[index]) {
        throw DuplicateComponent();
      } else {
        components[index] = component;
      }
    } else {
      while (components.size() < index) {
        components.emplace_back();
      }
      components.emplace_back(std::move(component));
    }
    
    if constexpr (OBJECT_PTR) {
      component->*OBJECT_PTR = static_cast<Object *>(this);
    }
  }
  
  template <typename Comp>
  EnableIfComponent<void, Comp> remComp() {
    const size_t index = GetComponentID<Comp>::get();
    if (index < components.size()) {
      if constexpr (OBJECT_PTR) {
        components[index]->*OBJECT_PTR = nullptr;
      }
      components[index] = nullptr;
    }
  }
  
  template <typename Comp>
  EnableIfComponent<bool, Comp> hasComp() const {
    const size_t index = GetComponentID<Comp>::get();
    return index < components.size() && components[index];
  }
  
  template <typename Comp>
  EnableIfComponent<std::shared_ptr<Comp>, Comp> getComp() const {
    const size_t index = GetComponentID<Comp>::get();
    if (index < components.size()) {
      return Utils::safeDownCast<Comp>(components[index]);
    } else {
      throw NoComponent();
    }
  }
  
  template <typename Comp>
  EnableIfComponent<Comp &, Comp> getCompRef() const {
    const size_t index = GetComponentID<Comp>::get();
    if (index < components.size()) {
      return dynamic_cast<Comp &>(*components[index]);
    } else {
      throw NoComponent();
    }
  }
  
protected:
  std::vector<std::shared_ptr<Component>> components;
};

#endif
