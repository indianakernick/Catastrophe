//
//  launcher physics component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 5/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "launcher physics component.hpp"

#include "yaml helper.hpp"
#include "systems registry.hpp"
#include "proximity sensor physics component.hpp"
#include "../Libraries/Box2D/Dynamics/Joints/b2PrismaticJoint.h"

LauncherPhysicsComponent::LauncherPhysicsComponent(
  const YAML::Node &node,
  const YAML::Node &level
) : JointPhysicsComponent(node, level) {
  if (joint->GetType() != b2JointType::e_prismaticJoint) {
    throw std::runtime_error("Launcher entity should be a prismatic joint");
  }
  prisJoint = static_cast<b2PrismaticJoint *>(joint);
  trigger = getChild(level, "trigger").as<EntityID>();
}

void LauncherPhysicsComponent::preStep(float) {
  std::shared_ptr<PhysicsComponent> comp = Systems::physics->get(trigger).lock();
  if (!comp) {
    throw std::runtime_error("Invalid trigger entity ID");
  }
  auto proxComp = std::dynamic_pointer_cast<ProximitySensorPhysicsComponent>(comp);
  if (!proxComp) {
    throw std::runtime_error("Entity ID doesn't refer to a proximity sensor");
  }
  if (proxComp->playerIsClose()) {
    prisJoint->EnableMotor(true);
  } else {
    prisJoint->EnableMotor(false);
  }
}

void LauncherPhysicsComponent::postStep() {}
