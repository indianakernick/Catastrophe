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
#include "../Libraries/Box2D/Dynamics/b2Body.h"

void SimplePhysicsComponent::init(b2World &world, const YAML::Node &node) {
  body = loadBody(getChild(node, "body").Scalar(), world, node.as<Transform>());
  body->SetUserData(this);
}

void SimplePhysicsComponent::preStep(float) {}

void SimplePhysicsComponent::postStep() {}
