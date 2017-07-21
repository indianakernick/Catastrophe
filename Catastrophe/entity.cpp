//
//  entity.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "entity.hpp"

Entity::Entity()
  : rect(0, 0, 1, 1) {}

Entity::Entity(const Rect rect)
  : rect(rect) {}

void Entity::onMove(OnMoveDispatcher::SettableListener listener) {
  onMoveDispatcher.setListener(listener);
  movedFrom(rect);
}

void Entity::offMove() {
  onMoveDispatcher.remListener();
}

void Entity::movedFrom(const Rect prevRect) {
  onMoveDispatcher.dispatch(prevRect, rect);
}
