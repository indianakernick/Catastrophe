//
//  oscillating physics component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 23/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "oscillating physics component.hpp"

#include "yaml helper.hpp"
#include "physics file.hpp"
#include "systems registry.hpp"
#include <Simpleton/Math/interpolate.hpp>
#include "../Libraries/Box2D/Dynamics/b2Body.h"

namespace {
  int quadrant(const b2Vec2 vec) {
    if (vec.x >= 0) {
      if (vec.y >= 0) {
        return 1;
      } else {
        return 4;
      }
    } else {
      if (vec.y >= 0) {
        return 2;
      } else {
        return 3;
      }
    }
  }
  
  bool sameQuadrant(const b2Vec2 a, const b2Vec2 b) {
    return quadrant(a) == quadrant(b);
  }
}

OscillatingPhysicsComponent::OscillatingPhysicsComponent(
  const YAML::Node &node,
  const YAML::Node &level
) {
  body = loadBody(
    getChild(node, "body").Scalar(),
    Systems::physics->getWorld(),
    level.as<Transform>()
  );
  body->SetUserData(this);
  first = getChild(level, "first").as<b2Vec2>();
  second = getChild(level, "second").as<b2Vec2>();
  
  if (const YAML::Node &startNode = level["start"]) {
    const float start = startNode.as<float>();
    const b2Vec2 startPoint = {
      Math::lerp(start, first.x, second.x),
      Math::lerp(start, first.y, second.y)
    };
    body->SetTransform(startPoint, body->GetAngle());
  } else {
    body->SetTransform(first, body->GetAngle());
  }
  
  const float vel = getChild(level, "vel").as<float>();
  toSecond = second - first;
  toSecond.Normalize();
  toSecond *= vel;
  
  body->SetLinearVelocity(toSecond);
}

void OscillatingPhysicsComponent::preStep(float) {}

void OscillatingPhysicsComponent::postStep() {
  const b2Vec2 pos = body->GetPosition();
  const b2Vec2 vel = body->GetLinearVelocity();
  
  if (sameQuadrant(vel, toSecond)) {
    const b2Vec2 toPosFromSecond = pos - second;
    if (sameQuadrant(toPosFromSecond, toSecond)) {
      body->SetTransform(second, body->GetAngle());
      body->SetLinearVelocity(-toSecond);
    }
  } else {
    const b2Vec2 toPosFromFirst = pos - first;
    if (sameQuadrant(toPosFromFirst, -toSecond)) {
      body->SetTransform(first, body->GetAngle());
      body->SetLinearVelocity(toSecond);
    }
  }
}
