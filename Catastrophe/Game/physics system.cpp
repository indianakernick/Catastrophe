//
//  physics system.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "physics system.hpp"

#include "physics constants.hpp"

void PhysicsSystem::init() {
  world.emplace(GRAVITY);
  draw.emplace();
  contactListener.emplace();
  world->SetDebugDraw(&(*draw));
  world->SetContactListener(&(*contactListener));
}

void PhysicsSystem::quit() {
  world->SetContactListener(nullptr);
  world->SetDebugDraw(nullptr);
  contactListener = std::experimental::nullopt;
  draw = std::experimental::nullopt;
  world = std::experimental::nullopt;
}

b2World *PhysicsSystem::getWorld() {
  return world ? &(*world) : nullptr;
}

void PhysicsSystem::add(
  const EntityID entityID,
  const std::shared_ptr<PhysicsComponent> comp
) {
  components.emplace(entityID, comp);
}

void PhysicsSystem::rem(const EntityID entityID) {
  auto iter = components.find(entityID);
  if (iter == components.cend()) {
    return;
  }
  b2Body *const body = iter->second->getBody();
  if (body) {
    world->DestroyBody(body);
  }
  components.erase(iter);
}

void PhysicsSystem::update(const float delta) {
  world->Step(delta, 6, 2);
}

void PhysicsSystem::debugRender() {
  world->DrawDebugData();
}

void PhysicsSystem::attachRenderer(RenderingContext &newRenderer) {
  draw->attachRenderer(&newRenderer);
}

void PhysicsSystem::detachRenderer() {
  draw->detachRenderer();
}

ContactListener &PhysicsSystem::getContactListener() {
  return *contactListener;
}
