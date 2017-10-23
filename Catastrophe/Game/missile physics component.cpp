//
//  missile physics component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "missile physics component.hpp"

#include "b2 glm cast.hpp"
#include "missile ai component.hpp"
#include "destroyable spawn component.hpp"
#include "../Libraries/Box2D/Dynamics/b2Body.h"

void MissilePhysicsComponent::preStep(float) {
  const auto aiComp = getExpectedCompImpl<MissileAIComponent>();
  const glm::vec2 force = aiComp->getAcc() * body->GetMass();
  const float angle = std::atan2(force.y, force.x);
  body->SetTransform(body->GetPosition(), angle);
  body->ApplyForceToCenter(castToB2(force), true);
}

void MissilePhysicsComponent::postStep() {
  if (contacted) {
    getExpectedCompImpl<DestroyableSpawnComponent>()->kill();
  }
}

void MissilePhysicsComponent::beginContact() {
  contacted = true;
}
