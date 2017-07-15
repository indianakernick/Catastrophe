//
//  entity.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef entity_hpp
#define entity_hpp

#include <vector>
#include "rect.hpp"
#include "entity id.hpp"
#include "entity component.hpp"
#include "component container.hpp"

class EntityManager;

class Entity final : public ComponentContainer<Entity, EntityComponent, &EntityComponent::entity> {
public:
  Entity(EntityID, Rect);
  ~Entity() = default;
  
  void update(EntityManager &, uint64_t);

  EntityID getID() const;
  
  Rect rect;
  
private:
  EntityID id;
};



#endif
