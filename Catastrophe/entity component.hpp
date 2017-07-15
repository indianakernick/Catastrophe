//
//  entity component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 14/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef entity_component_hpp
#define entity_component_hpp

#include <cstdint>

class Entity;
class EntityManager;

template <
  typename Object,
  typename Component,
  Object *Component::*OBJECT_PTR
>
class ComponentContainer;

class EntityComponent {
public:
  EntityComponent() = default;
  virtual ~EntityComponent() = default;
  
  virtual void update(EntityManager &, uint64_t) = 0;
  
protected:
  inline Entity &getEntity() {
    return *entity;
  }
  
  inline Entity *getEntityPtr() {
    return entity;
  }
  
private:
  Entity *entity = nullptr;
  
  friend ComponentContainer<Entity, EntityComponent, &EntityComponent::entity>;
};

#endif
