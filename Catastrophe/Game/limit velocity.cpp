//
//  limit velocity.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "limit velocity.hpp"

#include <Simpleton/Math/clamp.hpp>

constexpr float INF = std::numeric_limits<float>::infinity();

b2Vec2 limitVel(const b2Vec2 vel, const b2Vec2 groundVel, const b2Vec2 maxSpeed) {
  const b2Vec2 relVel = vel - groundVel;
  return {
    Math::clampMag(relVel.x, maxSpeed.x) + groundVel.x,
    Math::clampMag(relVel.y, maxSpeed.y) + groundVel.y
  };
}

b2Vec2 limitVel(const b2Vec2 vel, const b2Vec2 groundVel, const float maxSpeed) {
  return limitVel(vel, groundVel, {maxSpeed, maxSpeed});
}

b2Vec2 limitVelX(const b2Vec2 vel, const b2Vec2 groundVel, const float maxSpeed) {
  return limitVel(vel, groundVel, {maxSpeed, INF});
}

b2Vec2 limitVelY(const b2Vec2 vel, const b2Vec2 groundVel, const float maxSpeed) {
  return limitVel(vel, groundVel, {INF, maxSpeed});
}
