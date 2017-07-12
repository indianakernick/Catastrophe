//
//  actor.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef actor_hpp
#define actor_hpp

#include "rect.hpp"
#include "entity id.hpp"
#include <Simpleton/Math/dir.hpp>

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

  //interface for model manager (game logic)
  virtual void update(uint64_t) = 0;

  //interface for model
  EntityID getID() const;

private:
  EntityID id;
};



#endif
