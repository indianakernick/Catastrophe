//
//  physics system.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "physics system.hpp"

#include "layer names.hpp"
#include "global flags.hpp"
#include "entity manager.hpp"
#include "render manager.hpp"
#include "physics constants.hpp"
#include "physics component.hpp"
#include "rendering context.hpp"
#include <Simpleton/Utils/profiler.hpp>

#include <iostream>

void PhysicsSystem::init(RenderManager &renderMan) {
  world.emplace(GRAVITY);
  contactListener.emplace();
  world->SetContactListener(&(*contactListener));
  if constexpr (ENABLE_DEBUG_PHYSICS_RENDER) {
    draw.emplace();
    debugRenderJob = std::make_shared<DebugRenderJob>(*world, *draw);
    renderMan.addJob(getLayerIndex("debug physics"), debugRenderJob);
    world->SetDebugDraw(&(*draw));
  }
}

void PhysicsSystem::quit() {
  if constexpr (ENABLE_DEBUG_PHYSICS_RENDER) {
    debugRenderJob->kill();
    world->SetDebugDraw(nullptr);
    draw = std::experimental::nullopt;
  }
  world->SetContactListener(nullptr);
  contactListener = std::experimental::nullopt;
  world = std::experimental::nullopt;
}

b2World *PhysicsSystem::getWorld() {
  return world ? &(*world) : nullptr;
}

void PhysicsSystem::add(
  const EntityID entityID,
  const CompPtr comp,
  const YAML::Node &node
) {
  assert(world);
  comp->init(*world, node);
  components.emplace(entityID, comp);
}

void PhysicsSystem::rem(const EntityID entityID) {
  assert(world);
  auto iter = components.find(entityID);
  if (iter != components.cend()) {
    iter->second->quit(*world);
    components.erase(iter);
  }
}

std::weak_ptr<PhysicsComponent> PhysicsSystem::get(const EntityID entityID) {
  auto iter = components.find(entityID);
  if (iter == components.cend()) {
    return {};
  } else {
    return iter->second;
  }
}

void PhysicsSystem::update(const float delta) {
  PROFILE(PhysicsSystem::update);
  
  for (auto c = components.cbegin(); c != components.cend(); ++c) {
    c->second->preStep(delta);
  }

  world->Step(delta, VELOCITY_ITER, POSITION_ITER);
  
  for (auto c = components.cbegin(); c != components.cend(); ++c) {
    c->second->postStep();
  }
}

ContactListener &PhysicsSystem::getContactListener() {
  return *contactListener;
}

PhysicsSystem::DebugRenderJob::DebugRenderJob(b2World &world, DebugDraw &debugDraw)
  : world(world), debugDraw(debugDraw) {}

void PhysicsSystem::DebugRenderJob::render(RenderingContext &context) {
  PROFILE(Debug physics render);
  debugDraw.setContext(context.getContext());
  world.DrawDebugData();
}
