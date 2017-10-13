//
//  b2 helper.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 13/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "b2 helper.hpp"

b2AABB bodyAABB(const b2Body *body) {
  assert(body);
  
  b2AABB aabb;
  constexpr float MAX = std::numeric_limits<float>::max();
  aabb.lowerBound = b2Vec2(MAX, MAX);
  aabb.upperBound = b2Vec2(-MAX, -MAX);
  
  const b2Transform transform = body->GetTransform();
  const b2Fixture *fixture = body->GetFixtureList();
  
  while (fixture) {
    const b2Shape *shape = fixture->GetShape();
    if (!shape) continue;
    const int32 childCount = shape->GetChildCount();
    
    for (int32 child = 0; child != childCount; ++child) {
      b2AABB shapeAABB;
      shape->ComputeAABB(&shapeAABB, transform, child);
      aabb.Combine(shapeAABB);
    }
    
    fixture = fixture->GetNext();
  }
  return aabb;
}
