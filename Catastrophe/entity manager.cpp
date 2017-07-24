//
//  entity manager.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "entity manager.hpp"

EntityManager::EntityNotFound::EntityNotFound()
  : std::runtime_error("Entity not found") {}

void EntityManager::add(const EntityID id, std::unique_ptr<Entity> entity) {
  entities.add(id, entity);
}

void EntityManager::rem(const EntityID id) {
  entities.rem(id);
}

Entity *EntityManager::get(const EntityID id) const {
  const EntityMap &entityMap = entities.view();
  auto iter = entityMap.find(id);
  if (iter == entityMap.cend()) {
    throw EntityNotFound();
  } else {
    return iter->second.get();
  }
}

void EntityManager::update(const float delta) {
  EntityMap &entityMap = entities.startModifying();
  for (auto e = entityMap.cbegin(); e != entityMap.cend(); ++e) {
    e->second->update(*this, delta);
  }
  entities.stopModifying();
}

void EntityManager::render(RenderingContext &renderingContext) const {
  const EntityMap &entityMap = entities.view();
  for (auto e = entityMap.cbegin(); e != entityMap.cend(); ++e) {
    e->second->render(renderingContext);
  }
}
