//
//  physics system.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "physics system.hpp"

const b2Vec2 PhysicsSystem::GRAVITY = {0.0f, -9.80665f};

void PhysicsSystem::init(SDL_Renderer *renderer) {
  world.emplace(GRAVITY);
  draw.emplace(renderer);
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
