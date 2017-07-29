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
#include "rendering system.hpp"

void EntityManager::init(InputSystem &newInput, PhysicsSystem &newPhysics, RenderingSystem &newRendering) {
  input = &newInput;
  physics = &newPhysics;
  rendering = &newRendering;
}

void EntityManager::quit() {
  entities.clear();
  rendering = nullptr;
  physics = nullptr;
  input = nullptr;
}

void EntityManager::destroy(const EntityID id) {
  rendering->rem(id);
  physics->destroy(id);
  input->rem(id);
  entities.erase(id);
}

void EntityManager::update(const float delta) {
  for (auto e = entities.cbegin(); e != entities.cend(); ++e) {
    e->second->update(delta);
  }
}
