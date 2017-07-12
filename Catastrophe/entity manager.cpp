//
//  entity manager.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "entity manager.hpp"

void EntityManager::update(const uint64_t delta) {
  for (auto e = entities.cbegin(); e != entities.cend(); ++e) {
    e->second->update(delta);
  }
}

void EntityManager::addEntity(const std::shared_ptr<Entity> entity) {
  entities.emplace(entity->getID(), entity);
}

void EntityManager::remEntity(const EntityID id) {
  entities.erase(id);
}
