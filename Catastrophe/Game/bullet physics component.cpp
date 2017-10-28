//
//  bullet physics component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 22/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "bullet physics component.hpp"

#include "yaml helper.hpp"
#include "destroyable spawn component.hpp"
#include "../Libraries/Box2D/Dynamics/b2Body.h"

void BulletPhysicsComponent::init(b2World &world, const YAML::Node &node) {
  BodyPhysicsComponent::init(world, node);
  const float angle = body->GetAngle();
  float speed = 1.0f;
  getOptional(speed, node, "speed");
  const b2Vec2 vel = {std::cos(angle) * speed, std::sin(angle) * speed};
  body->SetLinearVelocity(vel);
}

void BulletPhysicsComponent::postStep() {
  if (contacted) {
    getExpectedCompImpl<DestroyableSpawnComponent>()->kill();
  }
}

void BulletPhysicsComponent::beginContact() {
  contacted = true;
}
