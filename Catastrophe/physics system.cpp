//
//  physics system.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 23/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "physics system.hpp"

void moveRectToTouch(Rect &a, const Rect b) {
  using ToIndex = Math::ToNum<size_t>;
  
  const float dists[4] = {
    a.top() - b.bottom(),
    a.right() - b.left(),
    a.bottom() - b.top(),
    a.left() - b.right()
  };
  
  float minDist = std::numeric_limits<float>::max();
  Math::Dir minDir = Math::Dir::NONE;
  for (Math::Dir d = Math::Dir::BEGIN; d != Math::Dir::END; ++d) {
    const float dist = std::abs(dists[ToIndex::conv(d)]);
    if (dist <= minDist) {
      minDist = dist;
      minDir = d;
    }
  }
  
  a.side(minDir, a.side(minDir) - dists[ToIndex::conv(minDir)]);
}

void PhysicsSystem::update(const float delta) {
  assert(!updating);
  
  updating = true;
  
  for (auto o = objects.begin(); o != objects.end(); ++o) {
    PhysicalObject &object = **o;
    object.rect.p += object.vel * delta;
    object.vel = {0.0f, 0.0f};
  }
  
  for (auto a = objects.begin(); a != objects.end(); ++a) {
    PhysicalObject &objectA = **a;
    for (auto b = std::next(a); b != objects.end(); ++b) {
      PhysicalObject &objectB = **b;
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
  
  for (auto o = removedObjects.cbegin(); o != removedObjects.cend(); ++o) {
    objects.erase(*o);
  }
  removedObjects.clear();
  
  updating = false;
}

void PhysicsSystem::addObject(std::shared_ptr<PhysicalObject> object) {
  assert(object);
  objects.emplace(object);
}

void PhysicsSystem::remObject(std::shared_ptr<PhysicalObject> object) {
  assert(object);
  if (updating) {
    removedObjects.emplace_back(objects.find(object));
  } else {
    objects.erase(object);
  }
}
