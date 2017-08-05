//
//  entity.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "entity.hpp"

#include "input component.hpp"
#include "render component.hpp"
#include "physics component.hpp"
#include "../Libraries/Box2D/Dynamics/b2Body.h"

Entity::Entity(const EntityID id)
  : id(id) {}

void Entity::update(const float delta) {
  if (input) {
    input->update(this, delta);
  }
  if (physics) {
    pos = physics->getPos();
  }
  if (render) {
    render->update(this, delta);
  }
}

EntityID Entity::getID() const {
  return id;
}

b2Vec2 Entity::getPos() const {
  return pos;
}
