//
//  factory functions.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 23/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "factory functions.hpp"

#include "bullet.hpp"
#include "factory.hpp"
#include "entity manager.hpp"
#include "bullet factory data.hpp"

void makeBullet(
  EntityManager &entityManager,
  PhysicsSystem &,
  const EntityID id,
  const glm::vec2 pos,
  const Utils::Any data
) {
  const BulletFactoryData bulletData = data.as<BulletFactoryData>();
  std::unique_ptr<Entity> bullet = std::make_unique<Bullet>(
    id,
    pos,
    bulletData.spec,
    bulletData.dir
  );
  entityManager.add(id, std::move(bullet));
}

void registerFactoryFunctions() {
  Factory::registerFunction<Bullet>(&makeBullet);
}
