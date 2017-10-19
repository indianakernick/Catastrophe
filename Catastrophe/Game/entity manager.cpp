//
//  entity manager.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "entity manager.hpp"

#include "systems.hpp"
#include "level file.hpp"
#include "entity file.hpp"
#include "player constants.hpp"

void EntityManager::init() {}

void EntityManager::quit() {
  entities.clear();
}

EntityID EntityManager::create(const std::string &fileName, const YAML::Node &levelArgs) {
  EntityID id = nextID;
  if (const YAML::Node &idNode = levelArgs["id"]) {
    id = idNode.as<EntityID>();
    if (id < nextID) {
      throw std::runtime_error("Invalid ID in level file");
    }
  }
  nextID = id + 1;
  createImpl(id, fileName, levelArgs);
  return id;
}

EntityID EntityManager::createPlayer(const std::string &fileName, const YAML::Node &levelArgs) {
  createImpl(PLAYER_ID, fileName, levelArgs);
  return PLAYER_ID;
}

void EntityManager::destroy(const EntityID id) {
  destroyComponents(id);
  entities.erase(id);
}

void EntityManager::destroyAll() {
  for (auto &e : entities) {
    destroyComponents(e.first);
  }
  entities.clear();
}

Entity &EntityManager::getEntity(const EntityID id) {
  auto iter = entities.find(id);
  if (iter == entities.end()) {
    throw std::runtime_error("Tried to get entity that does not exist");
  } else {
    return *(iter->second);
  }
}

void EntityManager::loadLevel(const std::string &fileName) {
  ::loadLevel(fileName, *this);
}

EntityID EntityManager::getNextID() const {
  return nextID;
}

void EntityManager::createImpl(
  const EntityID id,
  const std::string &fileName,
  const YAML::Node &levelArgs
) {
  auto entity = std::make_unique<Entity>(id);
  loadEntity(entity.get(), fileName, levelArgs);
  const auto [iter, inserted] = entities.emplace(id, std::move(entity));
  assert(inserted);
}

void EntityManager::destroyComponents(const EntityID id) const {
  //The components aren't removed in reverse order but I don't think that matters
  #define COMPONENT(N, ID_NAME) Systems::ID_NAME->rem(id);
  #define LAST_COMPONENT(N, ID_NAME)
  COMPONENTS
  #undef LAST_COMPONENT
  #undef COMPONENT
}
