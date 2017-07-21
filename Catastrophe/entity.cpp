//
//  entity.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "entity.hpp"

Entity::Entity(const EntityID id)
  : rect(0, 0, 1, 1), id(id) {}

Entity::Entity(const EntityID id, const Rect rect)
  : rect(rect), id(id) {}

void Entity::onMove(OnMoveDispatcher::SettableListener listener) {
  onMoveDispatcher.setListener(listener);
  movedFrom(rect);
}

void Entity::offMove() {
  onMoveDispatcher.remListener();
}

EntityID Entity::getID() const {
  return id;
}

void Entity::movedFrom(const Rect prevRect) {
  onMoveDispatcher.dispatch(prevRect, rect);
}
