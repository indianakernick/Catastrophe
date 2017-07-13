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
#include <Simpleton/Math/dir.hpp>

class EntityManager;

class Entity {
public:
  explicit Entity(EntityID);
  virtual ~Entity() = default;

  //interface for controller
  virtual void startMoving(Math::Dir) = 0;
  virtual void stopMoving() = 0;
  
  //interface for view. The view cannot modify the model
  virtual Rect getRect() const = 0;
  virtual bool isMoving() const = 0;
  virtual Math::Dir getMotionDir() const = 0;
  virtual float getMotionProgress() const = 0;

  //interface for EntityManager
  virtual void update(EntityManager &, uint64_t) = 0;
  ///Can an entity collide with this entity?
  virtual bool entityCanCollide(Entity *) = 0;
  ///An entity has collided with this entity
  virtual void onEntityCollision(Entity *) = 0;
  ///This entity has collided with another entity
  virtual void onCollisionWithEntity(Entity *) = 0;

  //interface for model
  EntityID getID() const;

private:
  EntityID id;
};



#endif
