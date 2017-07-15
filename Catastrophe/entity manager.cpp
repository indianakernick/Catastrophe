//
//  entity manager.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "entity manager.hpp"

#include "entity collision component.hpp"

void EntityManager::update(const uint64_t delta) {
  for (auto e = entities.cbegin(); e != entities.cend(); ++e) {
    e->second->update(*this, delta);
  }
}

void EntityManager::addEntity(const std::shared_ptr<Entity> entity) {
  entities.emplace(entity->getID(), entity);
}

void EntityManager::remEntity(const EntityID id) {
  entities.erase(id);
}

std::shared_ptr<Entity> EntityManager::getEntity(const EntityID id) {
  return entities.at(id);
}

bool EntityManager::entityCanMoveTo(Entity *entity, const Rect dest) const {
  //@TODO use spacial partioning when performance becomes an issue
  
  for (auto e = entities.cbegin(); e != entities.cend(); ++e) {
    if (e->second.get() == entity) {
      continue;
    }
    if (dest.interceptsWith(e->second->rect) && e->second->hasComp<EntityCollisionComponent>()) {
      if (!e->second->getCompRef<EntityCollisionComponent>().entityCanCollide(entity)) {
        return false;
      }
    }
  }
  return true;
}

void EntityManager::onEntityMove(Entity *entity) {
  const Rect entityRect = entity->rect;
  for (auto e = entities.cbegin(); e != entities.cend(); ++e) {
    if (entityRect.interceptsWith(e->second->rect)) {
      if (e->second->hasComp<EntityCollisionComponent>()) {
        e->second->getCompRef<EntityCollisionComponent>().onEntityCollision(entity);
      }
      if (entity->hasComp<EntityCollisionComponent>()) {
        entity->getCompRef<EntityCollisionComponent>().onCollisionWithEntity(e->second.get());
      }
    }
  }
}
