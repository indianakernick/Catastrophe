//
//  proximity sensor physics component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 5/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "proximity sensor physics component.hpp"

#include "yaml helper.hpp"
#include "physics file.hpp"
#include "systems registry.hpp"

ProximitySensorPhysicsComponent::ProximitySensorPhysicsComponent(
  const YAML::Node &node,
  const YAML::Node &level
) {
  Transform transform = level.as<Transform>();
  body = loadBody(getChild(node, "body").Scalar(), Systems::physics->getWorld(), transform);
  body->SetUserData(this);
}

void ProximitySensorPhysicsComponent::preStep(float) {}

void ProximitySensorPhysicsComponent::postStep() {}

void ProximitySensorPhysicsComponent::beginContactingPlayer() {
  contacting = true;
}

void ProximitySensorPhysicsComponent::endContactingPlayer() {
  contacting = false;
}

bool ProximitySensorPhysicsComponent::playerIsClose() const {
  return contacting;
}
