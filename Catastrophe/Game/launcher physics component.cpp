//
//  launcher physics component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 5/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "launcher physics component.hpp"

#include "systems.hpp"
#include "b2 glm cast.hpp"
#include "yaml helper.hpp"
#include <Simpleton/Math/clamp.hpp>
#include "button physics component.hpp"
#include <Simpleton/Math/interpolate.hpp>
#include <Simpleton/Utils/safe down cast.hpp>
#include "../Libraries/Box2D/Dynamics/Joints/b2PrismaticJoint.h"

void LauncherPhysicsComponent::init(b2World &world, const YAML::Node &node) {
  JointPhysicsComponent::init(world, node);
  if (joint->GetType() != b2JointType::e_prismaticJoint) {
    throw std::runtime_error("Launcher entity should be a prismatic joint");
  }
  prisJoint = static_cast<b2PrismaticJoint *>(joint);
  trigger = getChild(node, "trigger").as<EntityID>();
}

void LauncherPhysicsComponent::preStep(float) {
  std::shared_ptr<PhysicsComponent> comp = Systems::physics->get(trigger).lock();
  if (!comp) {
    throw std::runtime_error("Invalid trigger entity ID");
  }
  auto buttonComp = Utils::safeDownCast<ButtonPhysicsComponent>(comp);
  if (buttonComp->playerOnButton()) {
    prisJoint->EnableMotor(true);
  } else {
    prisJoint->EnableMotor(false);
  }
}

float LauncherPhysicsComponent::getRelTranslation() const {
  return Math::clamp(
    Math::invLerp<float>(
      prisJoint->GetJointTranslation(),
      prisJoint->GetLowerLimit(),
      prisJoint->GetUpperLimit()
    ),
    0.0f,
    1.0f
  );
}

float LauncherPhysicsComponent::getLimitSize() const {
  return prisJoint->GetUpperLimit() - prisJoint->GetLowerLimit();
}

namespace {
  b2Vec2 rotate(const b2Vec2 v, const float a) {
    return {
      v.x * std::cos(a) - v.y * std::sin(a),
      v.x * std::sin(a) + v.y * std::cos(a)
    };
  }
  
  float angle(const b2Vec2 v) {
    return std::atan2(v.y, v.x);
  }
}

glm::vec2 LauncherPhysicsComponent::getCenter() const {
  const float middleTranslation = Math::middle(
    prisJoint->GetLowerLimit(),
    prisJoint->GetUpperLimit()
  );
  const b2Vec2 axisA = rotate(
    prisJoint->GetLocalAxisA(),
    prisJoint->GetBodyA()->GetAngle()
  );
  return castToGLM(prisJoint->GetAnchorA() + middleTranslation * axisA);
}

float LauncherPhysicsComponent::getRotation() const {
  return prisJoint->GetBodyA()->GetAngle() + angle(prisJoint->GetLocalAxisA());
}
