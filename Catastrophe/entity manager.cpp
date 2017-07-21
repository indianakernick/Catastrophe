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

Entity *EntityManager::get(const EntityID id) const {
  auto iter = entities.find(id);
  if (iter == entities.cend()) {
    throw EntityNotFound();
  } else {
    return iter->second.get();
  }
}

void EntityManager::update(const float delta) const {
  for (auto e = entities.cbegin(); e != entities.cend(); ++e) {
    e->second->update(delta);
  }
}

void EntityManager::render(RenderingContext &renderingContext) const {
  for (auto e = entities.cbegin(); e != entities.cend(); ++e) {
    e->second->render(renderingContext);
  }
}
