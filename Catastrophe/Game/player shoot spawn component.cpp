//
//  player shoot spawn component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "player shoot spawn component.hpp"

#include <random>
#include "yaml helper.hpp"
#include "body physics component.hpp"
#include "player input component.hpp"

void PlayerShootSpawnComponent::init(const YAML::Node &node) {
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

void PlayerShootSpawnComponent::update(const float delta) {
  static std::mt19937 gen;

  const auto inputComp = getExpectedCompImpl<const PlayerInputComponent>();
  
  frequency.advance(delta);
  if (inputComp->shouldShoot()) {
    willSpawn = frequency.canDo();
    if (willSpawn) {
      const glm::vec2 pos = getExpectedCompImpl<BodyPhysicsComponent>()->getPos();
      levelNode["pos"] = pos;
      const glm::vec2 toTarget = inputComp->getGunTarget() - pos;
      const float angle = std::atan2(toTarget.y, toTarget.x);
      std::normal_distribution<float> dist(angle, bulletSpread);
      levelNode["rotation"] = angleToFile(dist(gen));
    }
  } else {
    willSpawn = false;
  }
}

EntityID PlayerShootSpawnComponent::shouldSpawnEntities() const {
  return willSpawn;
}

std::string PlayerShootSpawnComponent::getEntityFile(EntityID) const {
  return entityFile;
}

YAML::Node PlayerShootSpawnComponent::getLevelNode(EntityID) const {
  return levelNode;
}
