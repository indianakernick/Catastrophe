//
//  factory.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 23/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "factory.hpp"

#include "entity manager.hpp"
#include "physics system.hpp"

EntityManager *Factory::entityManager = nullptr;
PhysicsSystem *Factory::physicsSystem = nullptr;
std::unordered_map<size_t, Factory::FactoryFunction> Factory::factoryFunctions = {};
ID::Local<EntityID> Factory::idGen;
bool Factory::wasCreated = false;

void Factory::init(EntityManager &entityManagerRef, PhysicsSystem &physicsSystemRef) {
  assert(!wasCreated);
  entityManager = &entityManagerRef;
  physicsSystem = &physicsSystemRef;
  wasCreated = true;
}

void Factory::quit() {
  assert(wasCreated);
  entityManager = nullptr;
  physicsSystem = nullptr;
  wasCreated = false;
}

void Factory::kill(const EntityID id) {
  assert(wasCreated);
  physicsSystem->rem(id);
  entityManager->rem(id);
}
