//
//  entity.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "entity.hpp"

Entity::Entity(const EntityID id)
  : id(id) {}

EntityID Entity::getID() const {
  return id;
}
