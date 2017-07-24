//
//  physics system.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 23/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "physics system.hpp"

void PhysicsSystem::add(
  const EntityID id,
  std::shared_ptr<PhysicalObject> object
) {
  assert(object);
  objects.add(id, object);
}

void PhysicsSystem::rem(const EntityID id) {
  objects.rem(id);
}

void moveRectToTouch(Rect &a, const Rect b) {
  const float dists[4] = {
    a.top() - b.bottom(),
    a.right() - b.left(),
    a.bottom() - b.top(),
    a.left() - b.right()
  };
  
  float minDist = std::numeric_limits<float>::max();
  Math::Dir minDir = Math::Dir::NONE;
  for (Math::Dir d = Math::Dir::BEGIN; d != Math::Dir::END; ++d) {
    const float dist = std::abs(dists[static_cast<size_t>(d)]);
    if (dist <= minDist) {            
      minDist = dist;
      minDir = d;
    }
  }
  
  a.side(minDir, a.side(minDir) - dists[static_cast<size_t>(minDir)]);
}

void PhysicsSystem::update(const float delta) {
  ObjectMap &objectMap = objects.startModifying();
  
  for (auto o = objectMap.begin(); o != objectMap.end(); ++o) {
    PhysicalObject &object = *(o->second);
    object.rect.p += object.vel * delta;
    object.vel = {0.0f, 0.0f};
  }
  
  for (auto a = objectMap.begin(); a != objectMap.end(); ++a) {
    PhysicalObject &objectA = *(a->second);
    for (auto b = std::next(a); b != objectMap.end(); ++b) {
      PhysicalObject &objectB = *(b->second);
      if (
        objectA.collidable &&
        objectB.collidable &&
        objectA.rect.interceptsWith(objectB.rect)
      ) {
        if (objectA.mass < objectB.mass) {
          moveRectToTouch(objectA.rect, objectB.rect);
        } else if (objectA.mass > objectB.mass || objectA.mass != PhysicalObject::FIXED) {
          moveRectToTouch(objectB.rect, objectA.rect);
        }
        objectA.collisionDispatcher.dispatch(objectB.entity);
        objectB.collisionDispatcher.dispatch(objectA.entity);
      }
    }
  }
  
  objects.stopModifying();
}
