//
//  simple physics component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 3/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "simple physics component.hpp"

#include "yaml helper.hpp"
#include "physics file.hpp"
#include "systems registry.hpp"
#include "../Libraries/Box2D/Dynamics/b2Body.h"

SimplePhysicsComponent::SimplePhysicsComponent(
  const YAML::Node &node,
  const YAML::Node &level
) {
  body = loadBody(
    getChild(node, "body").Scalar(),
    Systems::physics->getWorld(),
    readTransform(level)
  );
  body->SetUserData(this);
}

void SimplePhysicsComponent::preStep(float) {}

void SimplePhysicsComponent::postStep() {}
