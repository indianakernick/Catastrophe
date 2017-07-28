//
//  physics system.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "physics system.hpp"

const b2Vec2 PhysicsSystem::GRAVITY = {0.0f, -9.80665f};

void PhysicsSystem::init() {
  world.emplace(GRAVITY);
}

void PhysicsSystem::quit() {
  world = std::experimental::nullopt;
}

std::shared_ptr<PhysicsComponent> PhysicsSystem::create(
  const EntityID entityID,
  const b2BodyDef bodyDef
) {
  auto comp = std::make_shared<PhysicsComponent>();
  comp->body = world->CreateBody(&bodyDef);
  components.emplace(entityID, comp);
  return comp;
}

void PhysicsSystem::destroy(const EntityID entityID) {
  auto iter = components.find(entityID);
  if (iter == components.cend()) {
    return;
  }
  world->DestroyBody(iter->second->body);
  components.erase(iter);
}

void PhysicsSystem::update(const float delta) {
  world->Step(delta, 6, 2);
}
