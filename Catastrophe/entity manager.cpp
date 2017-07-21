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

void EntityManager::kill(const EntityID id) {
  if (updating) {
    killedEntities.emplace_back(entities.find(id));
  } else {
    entities.erase(id);
  }
}

Entity *EntityManager::get(const EntityID id) const {
  auto iter = entities.find(id);
  if (iter == entities.cend()) {
    throw EntityNotFound();
  } else {
    return iter->second.get();
  }
}

void EntityManager::update(const float delta) {
  assert(!updating);
  updating = true;
  for (auto e = entities.cbegin(); e != entities.cend(); ++e) {
    e->second->update(*this, delta);
  }
  updating = false;
  
  for (auto e = killedEntities.cbegin(); e != killedEntities.cend(); ++e) {
    entities.erase(*e);
  }
  killedEntities.clear();
}

void EntityManager::render(RenderingContext &renderingContext) const {
  for (auto e = entities.cbegin(); e != entities.cend(); ++e) {
    e->second->render(renderingContext);
  }
}
