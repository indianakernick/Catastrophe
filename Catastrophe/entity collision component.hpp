//
//  entity collision component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 14/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef entity_collision_component_hpp
#define entity_collision_component_hpp

#include "entity component.hpp"

class EntityCollisionComponent : public EntityComponent {
public:
  EntityCollisionComponent() = default;
  ~EntityCollisionComponent() = default;

  ///Can an entity collide with this entity?
  virtual bool entityCanCollide(Entity *) = 0;
  ///An entity has collided with this entity
  virtual void onEntityCollision(Entity *) = 0;
  ///This entity has collided with another entity
  virtual void onCollisionWithEntity(Entity *) = 0;
  
  void update(EntityManager &, uint64_t) override {}
};

#endif
