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

Rect Entity::getRect() const {
  return rect;
}

EntityID Entity::getID() const {
  return id;
}
