//
//  static entity.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 13/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "static entity.hpp"

StaticEntity::StaticEntity(const EntityID id, const Rect rect)
  : Entity(id, rect) {}

StaticEntity::~StaticEntity() {}
