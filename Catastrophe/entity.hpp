//
//  entity.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef entity_hpp
#define entity_hpp

#include "rect.hpp"
#include "entity id.hpp"

class EntityManager;

class Entity {
public:
  Entity(EntityID, Rect);
  virtual ~Entity() = default;
  
  virtual void update(EntityManager &, uint64_t) = 0;
  ///Can an entity collide with this entity?
  virtual bool entityCanCollide(Entity *) = 0;
  ///An entity has collided with this entity
  virtual void onEntityCollision(Entity *) = 0;
  ///This entity has collided with another entity
  virtual void onCollisionWithEntity(Entity *) = 0;

  Rect getRect() const;
  EntityID getID() const;

protected:
  Rect rect;

private:
  EntityID id;
};



#endif
