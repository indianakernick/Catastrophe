//
//  destroyable spawn component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "destroyable spawn component.hpp"

void DestroyableSpawnComponent::init(const YAML::Node &) {}

void DestroyableSpawnComponent::update(float) {}

bool DestroyableSpawnComponent::shouldDestroySelf() {
  return dead;
}

EntityID DestroyableSpawnComponent::shouldSpawnEntities() {
  return 0;
}

void DestroyableSpawnComponent::setFirstID(EntityID) {}

std::string DestroyableSpawnComponent::getEntityFile(EntityID) {
  return {};
}

YAML::Node DestroyableSpawnComponent::getLevelNode(EntityID) {
  return {};
}

void DestroyableSpawnComponent::kill() {
  dead = true;
}
