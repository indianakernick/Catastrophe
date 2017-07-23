//
//  physical object.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 23/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef physical_object_hpp
#define physical_object_hpp

#include "rect.hpp"
#include "entity id.hpp"
#include <Simpleton/Utils/dispatcher.hpp>

class PhysicalObject {
private:
  friend class PhysicsSystem;
  
  using CollisionDispatcher = Utils::SingleDispatcher<
    void (EntityID),
    void
  >;

public:
  static constexpr unsigned FIXED = std::numeric_limits<unsigned>::max();

  PhysicalObject(EntityID, Rect, unsigned, bool);
  
  EntityID getID() const;
  Rect getRect() const;
  
  void setVelocity(glm::vec2);
  
  void onCollision(CollisionDispatcher::SettableListener);
  void offCollision();
  
private:
  CollisionDispatcher collisionDispatcher;
  EntityID entity;
  Rect rect;
  glm::vec2 vel;
  unsigned mass;
  bool collidable;
};

#endif
