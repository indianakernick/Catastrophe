//
//  entity manager.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "entity manager.hpp"

#include "level file.hpp"
#include "entity file.hpp"
#include "systems registry.hpp"

void EntityManager::init() {}

void EntityManager::quit() {
  entities.clear();
}

EntityID EntityManager::create(const std::string &fileName, const YAML::Node &levelArgs) {
  std::unique_ptr<Entity> entity = loadEntity(fileName, levelArgs);
  const EntityID id = entity->getID();
  entities.emplace(id, std::move(entity));
  return id;
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

EntityID EntityManager::loadLevel(const std::string &fileName) {
  lastID = ::loadLevel(fileName, *this);
  return lastID;
}

EntityID EntityManager::getLastID() const {
  return lastID;
}

void EntityManager::destroyComponents(const EntityID id) const {
  Systems::rendering->rem(id);
  Systems::animation->rem(id);
  Systems::physics->rem(id);
  Systems::spawn->rem(id);
  Systems::input->rem(id);
}
