//
//  spawn component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "spawn component.hpp"

bool SpawnComponent::shouldDestroySelf() const {
  return false;
}

EntityID SpawnComponent::shouldSpawnEntities() const {
  return 0;
}

void SpawnComponent::setFirstID(EntityID) {}

std::string SpawnComponent::getEntityFile(EntityID) const {
  return {};
}

YAML::Node SpawnComponent::getLevelNode(EntityID) const {
  return {};
}
