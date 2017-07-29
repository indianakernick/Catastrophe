//
//  entity.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "entity.hpp"

#include "input component.hpp"
#include "visible component.hpp"
#include "physics component.hpp"
#include "../Libraries/Box2D/Dynamics/b2Body.h"

Entity::Entity(const EntityID id)
  : id(id) {}

void Entity::update() {
  if (input) {
    input->update();
  }
  if (physics && visual) {
    const b2Vec2 pos = physics->body->GetPosition();
    visual->rect.p = {pos.x, pos.y};
    visual->rect.s = {1.0f, 1.0f};
  }
}

EntityID Entity::getID() const {
  return id;
}
