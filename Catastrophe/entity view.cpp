//
//  entity view.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "entity view.hpp"

#include <cassert>

EntityView::EntityView(Entity *entity)
  : entity(entity) {
  assert(entity);
}

void EntityView::setEntity(Entity *newEntity) {
  assert(newEntity);
  entity = newEntity;
}
