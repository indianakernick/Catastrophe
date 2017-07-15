//
//  entity.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "entity.hpp"

Entity::Entity(const EntityID id, const Rect rect)
  : rect(rect), id(id) {}

void Entity::update(EntityManager &entityMan, const uint64_t delta) {
  updateComps(&EntityComponent::update, entityMan, delta);
}

EntityID Entity::getID() const {
  return id;
}
