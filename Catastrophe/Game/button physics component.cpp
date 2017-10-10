//
//  button physics component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 5/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "button physics component.hpp"

#include "yaml helper.hpp"
#include "physics file.hpp"

void ButtonPhysicsComponent::init(b2World &world, const YAML::Node &node) {
  Transform transform = node.as<Transform>();
  body = loadBody(getChild(node, "body").Scalar(), world, transform);
  body->SetUserData(this);
}

void ButtonPhysicsComponent::preStep(float) {}

void ButtonPhysicsComponent::postStep() {}

void ButtonPhysicsComponent::beginContactingPlayer() {
  contacting = true;
}

void ButtonPhysicsComponent::endContactingPlayer() {
  contacting = false;
}

bool ButtonPhysicsComponent::playerOnButton() const {
  return contacting;
}
