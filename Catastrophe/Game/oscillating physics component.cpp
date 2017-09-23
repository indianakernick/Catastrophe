//
//  oscillating physics component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 23/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "oscillating physics component.hpp"

#include "yaml helper.hpp"
#include "../Libraries/Box2D/Dynamics/b2Body.h"

namespace {
  b2Vec2 readVec(const YAML::Node &vecNode) {
    checkType(vecNode, YAML::NodeType::Sequence);
    
    if (vecNode.size() != 2) {
      throw std::runtime_error(
        "Vector at line "
        + std::to_string(vecNode.Mark().line)
        + " must have 2 components"
      );
    }
    
    return {
      vecNode[0].as<float32>(),
      vecNode[1].as<float32>()
    };
  }
  
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
  Entity *const entity,
  b2Body *const body,
  const YAML::Node &args
) : PhysicsComponent(entity, body),
    first(readVec(getChild(args, "first"))),
    second(readVec(getChild(args, "second"))) {
  
  assert(body->GetType() == b2_kinematicBody);
  body->SetTransform(first, body->GetAngle());
  
  const float vel = getChild(args, "vel").as<float>();
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
