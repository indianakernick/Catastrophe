//
//  world.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 13/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "world.hpp"

World::World(EntityFactory &factory, EntityManager &entityMan)
  : factory(factory), entityMan(entityMan) {}

void World::init() {
  playerID = factory.make("player", {0, 0, 1, 1});
}

void World::quit() {
  factory.destroy(playerID);
}

void World::update(uint64_t) {
  
}
