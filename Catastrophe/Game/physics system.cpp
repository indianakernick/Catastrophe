//
//  physics system.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "physics system.hpp"

#include "entity manager.hpp"
#include "physics constants.hpp"
#include "physics component.hpp"

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
  b2Body *const body = iter->second->body;
  if (body) {
    world->DestroyBody(body);
  }
  components.erase(iter);
}

void PhysicsSystem::update(EntityManager &entityMan, const float delta) {
  for (auto c = components.cbegin(); c != components.cend(); ++c) {
    const Entity &entity = entityMan.getEntity(c->first);
    const InputCommands &input = *entity.latestInputCommands;
    PhysicsState &physics = *entity.latestPhysicsState;
    c->second->preStep(physics, input, delta);
  }

  world->Step(delta, VELOCITY_ITER, POSITION_ITER);
  
  for (auto c = components.cbegin(); c != components.cend(); ++c) {
    const Entity &entity = entityMan.getEntity(c->first);
    const InputCommands &input = *entity.latestInputCommands;
    PhysicsState &physics = *entity.latestPhysicsState;
    c->second->postStep(physics, input);
  }
}

void PhysicsSystem::debugRender() {
  world->DrawDebugData();
}

void PhysicsSystem::attachRenderer(NVGcontext *newRenderer) {
  draw->attachRenderer(newRenderer);
}

void PhysicsSystem::detachRenderer() {
  draw->detachRenderer();
}

ContactListener &PhysicsSystem::getContactListener() {
  return *contactListener;
}
