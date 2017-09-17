//
//  entity manager.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "entity manager.hpp"

#include "input system.hpp"
#include "physics system.hpp"
#include "animation system.hpp"
#include "rendering system.hpp"

void EntityManager::init(
  InputSystem &newInput,
  PhysicsSystem &newPhysics,
  AnimationSystem &newAnimation,
  RenderingSystem &newRendering
) {
  input = &newInput;
  physics = &newPhysics;
  animation = &newAnimation;
  rendering = &newRendering;
}

void EntityManager::quit() {
  entities.clear();
  rendering = nullptr;
  animation = nullptr;
  physics = nullptr;
  input = nullptr;
}

void EntityManager::destroy(const EntityID id) {
  rendering->rem(id);
  animation->rem(id);
  physics->rem(id);
  input->rem(id);
  entities.erase(id);
}

Entity &EntityManager::getEntity(const EntityID id) {
  auto iter = entities.find(id);
  if (iter == entities.end()) {
    throw std::runtime_error("Tried to get entity that does not exist");
  } else {
    return *(iter->second);
  }
}

Systems EntityManager::getSystems() const {
  return {
    *input,
    *physics,
    *animation,
    *rendering
  };
}
