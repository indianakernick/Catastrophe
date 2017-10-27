//
//  droid shoot spawn component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 22/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "droid shoot spawn component.hpp"

#include <random>
#include "yaml helper.hpp"
#include "body physics component.hpp"
#include "ground droid ai component.hpp"

void DroidShootSpawnComponent::init(const YAML::Node &node) {
  float rof = 1.0f;
  getOptional(rof, node, "rof");
  frequency.setFrequency(rof);
  if (const YAML::Node &entity = node["entity"]) {
    getOptional(entityFile, entity, "file");
    levelNode = entity;
  }
  getOptional(bulletSpread, node, "bullet spread");
  bulletSpread = std::abs(angleFromFile(bulletSpread));
}

void DroidShootSpawnComponent::update(const float delta) {
  static std::mt19937 gen;

  const auto aiComp = getExpectedCompImpl<GroundDroidAIComponent>();
  
  frequency.advance(delta);
  if (aiComp->shouldShoot()) {
    willSpawn = frequency.canDo();
    if (willSpawn) {
      levelNode["pos"] = getExpectedCompImpl<BodyPhysicsComponent>()->getPos();
      std::normal_distribution<float> dist(aiComp->getGunAngle(), bulletSpread);
      levelNode["rotation"] = angleToFile(dist(gen));
    }
  } else {
    willSpawn = false;
  }
}

EntityID DroidShootSpawnComponent::shouldSpawnEntities() const {
  return willSpawn;
}

std::string DroidShootSpawnComponent::getEntityFile(EntityID) const {
  return entityFile;
}

YAML::Node DroidShootSpawnComponent::getLevelNode(EntityID) const {
  return levelNode;
}
