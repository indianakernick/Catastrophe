//
//  joint physics component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 4/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "joint physics component.hpp"

#include "b2 helper.hpp"
#include "yaml helper.hpp"
#include "physics file.hpp"
#include "systems registry.hpp"
#include "body physics component.hpp"

namespace {
  std::shared_ptr<BodyPhysicsComponent> getBodyComp(const YAML::Node &node) {
    const EntityID id = node.as<EntityID>();
    auto comp = Systems::physics->get(id).lock();
    if (!comp) {
      throw std::runtime_error(
        "Invalid entity ID at line "
        + std::to_string(node.Mark().line)
      );
    }
    auto bodyComp = std::dynamic_pointer_cast<BodyPhysicsComponent>(comp);
    if (!bodyComp || !bodyComp->getBody()) {
      throw std::runtime_error(
        "Expected entity at line "
        + std::to_string(node.Mark().line)
        + " to be a physics body"
      );
    }
    return bodyComp;
  }
}

void JointPhysicsComponent::init(b2World &world, const YAML::Node &node) {
  const auto bodyCompA = getBodyComp(getChild(node, "body A"));
  const auto bodyCompB = getBodyComp(getChild(node, "body B"));
  
  const YAML::Node &jointNode = getChild(node, "joint");
  b2JointDef *jointDef = loadJoint(jointNode.Scalar());
  jointDef->userData = this;
  jointDef->bodyA = bodyCompA->getBody();
  jointDef->bodyB = bodyCompB->getBody();
  
  readJoint(jointDef, node);
  
  joint = world.CreateJoint(jointDef);
}

void JointPhysicsComponent::quit(b2World &) {
  //a joint is destroyed when either of the bodies is destroyed
}

AABB JointPhysicsComponent::getAABB() const {
  b2AABB aabb = bodyAABB(joint->GetBodyA());
  aabb.Combine(bodyAABB(joint->GetBodyB()));
  return {
    castToGLM(aabb.lowerBound),
    castToGLM(aabb.upperBound)
  };
}
