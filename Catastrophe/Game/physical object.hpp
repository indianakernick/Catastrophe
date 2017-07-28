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
  using CollisionDispatcher = Utils::SingleDispatcher<
    void (EntityID),
    void
  >;

public:
  static constexpr float FIXED = std::numeric_limits<float>::max();

  PhysicalObject(EntityID, Rect, float, bool);
  
  EntityID getID() const;
  Rect getRect() const;
  
  void setRect(Rect);
  void setMass(float);
  void setCollidable(bool);
  
  void applyForce(glm::vec2);
  void applyImpulse(glm::vec2);
  
  void update(float, glm::vec2);
  
  void onCollision(CollisionDispatcher::SettableListener);
  void offCollision();
  
private:
  CollisionDispatcher collisionDispatcher;
  EntityID entity;
  Rect rect;
  glm::vec2 vel;
  glm::vec2 accel;
  glm::vec2 force;
  glm::vec2 impulse;
  float mass;
  bool collidable;
};

#endif
