//
//  body physics component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 11/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "body physics component.hpp"

#include <cassert>
#include "b2 glm cast.hpp"
#include "yaml helper.hpp"
#include "physics file.hpp"

void BodyPhysicsComponent::init(b2World &world, const YAML::Node &node) {
  body = loadBody(getChild(node, "body").Scalar(), world, node.as<Transform>());
  body->SetUserData(this);
}

void BodyPhysicsComponent::quit(b2World &world) {
  world.DestroyBody(body);
  body = nullptr;
}

glm::vec2 BodyPhysicsComponent::getPos() const {
  assert(body);
  return castToGLM(body->GetPosition());
}

float BodyPhysicsComponent::getAngle() const {
  assert(body);
  return body->GetAngle();
}

b2Body *BodyPhysicsComponent::getBody() {
  return body;
}

const b2Body *BodyPhysicsComponent::getBody() const {
  return body;
}
