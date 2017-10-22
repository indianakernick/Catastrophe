//
//  periodic spawn component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "periodic spawn component.hpp"

#include "yaml helper.hpp"

void PeriodicSpawnComponent::init(const YAML::Node &node) {
  float spawnTime = 1.0f;
  getOptional(spawnTime, node, "spawn time");
  frequency.setPeriod(spawnTime);
  if (const YAML::Node &entity = node["entity"]) {
    getOptional(entityFile, entity, "file");
    levelNode = entity;
  }
}

void PeriodicSpawnComponent::update(const float delta) {
  frequency.advance(delta);
  numEntitiesToSpawn = frequency.canDoMultipleOverlap();
}

EntityID PeriodicSpawnComponent::shouldSpawnEntities() const {
  return numEntitiesToSpawn;
}

std::string PeriodicSpawnComponent::getEntityFile(EntityID) const {
  return entityFile;
}

YAML::Node PeriodicSpawnComponent::getLevelNode(EntityID) const {
  return levelNode;
}
