//
//  spring board physics component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 4/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "spring board physics component.hpp"

#include "yaml helper.hpp"
#include "physics file.hpp"
#include "../Libraries/Box2D/Dynamics/Joints/b2DistanceJoint.h"

SpringBoardPhysicsComponent::SpringBoardPhysicsComponent(
  const YAML::Node &node,
  const YAML::Node &level,
  PhysicsSystem &physics
) {
  const YAML::Node &nodeA = getChild(level, "body A");
  const YAML::Node &nodeB = getChild(level, "body B");
  const EntityID idA = nodeA.as<EntityID>();
  const EntityID idB = nodeB.as<EntityID>();
  std::shared_ptr<PhysicsComponent> compA = physics.get(idA).lock();
  std::shared_ptr<PhysicsComponent> compB = physics.get(idB).lock();
  
  if (!compA || !compA->body) {
    throw std::runtime_error(
      "Invalid entity ID at line"
      + std::to_string(nodeA.Mark().line)
    );
  }
  if (!compB || !compB->body) {
    throw std::runtime_error(
      "Invalid entity ID at line"
      + std::to_string(nodeB.Mark().line)
    );
  }
  
  const YAML::Node &jointNode = getChild(node, "joint");
  b2JointDef *jointDef = loadJoint(jointNode.Scalar());
  jointDef->userData = this;
  jointDef->bodyA = compA->body;
  jointDef->bodyB = compB->body;
  
  if (jointDef->type != b2JointType::e_distanceJoint) {
    throw std::runtime_error(
      "Expected joint at file at line "
      + std::to_string(jointNode.Mark().line)
      + " to be a distance joint"
    );
  }
  
  b2DistanceJointDef *distJointDef = static_cast<b2DistanceJointDef *>(jointDef);
  distJointDef->localAnchorA = readB2vec(getChild(level, "local anchor A"));
  distJointDef->localAnchorB = readB2vec(getChild(level, "local anchor B"));
  
  joint = physics.getWorld()->CreateJoint(distJointDef);
}

void SpringBoardPhysicsComponent::preStep(float) {}

void SpringBoardPhysicsComponent::postStep() {}
