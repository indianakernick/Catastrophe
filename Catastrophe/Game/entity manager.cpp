//
//  entity manager.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "entity manager.hpp"

#include "entity file.hpp"
#include "systems registry.hpp"

void EntityManager::init() {}

void EntityManager::quit() {
  entities.clear();
}

void EntityManager::create(const std::string &filePath, const YAML::Node &levelArgs) {
  std::unique_ptr<Entity> entity = loadEntity(filePath, levelArgs);
  const EntityID id = entity->getID();
  entities.emplace(id, std::move(entity));
}

void EntityManager::destroy(const EntityID id) {
  Systems::rendering->rem(id);
  Systems::animation->rem(id);
  Systems::physics->rem(id);
  Systems::input->rem(id);
  entities.erase(id);
}

void EntityManager::destroyAll() {
  for (auto e = entities.cbegin(); e != entities.cend(); ++e) {
    const EntityID id = e->first;
    Systems::rendering->rem(id);
    Systems::animation->rem(id);
    Systems::physics->rem(id);
    Systems::input->rem(id);
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
