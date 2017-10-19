//
//  spawn system.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "spawn system.hpp"

#include <cassert>
#include "entity manager.hpp"
#include "spawn component.hpp"
#include <Simpleton/Utils/profiler.hpp>

void SpawnSystem::init(EntityManager &newEntityMan) {
  assert(!entityMan);
  entityMan = &newEntityMan;
}

void SpawnSystem::quit() {
  entityMan = nullptr;
}

void SpawnSystem::add(
  const EntityID id,
  const CompPtr comp,
  const YAML::Node &node
) {
  comp->init(node);
  components.emplace(id, comp);
}

void SpawnSystem::rem(const EntityID id) {
  components.erase(id);
}

void SpawnSystem::update(const float delta) {
  PROFILE(SpawnSystem::update);
  
  assert(entityMan);
  
  static std::vector<EntityID> dead;
  static std::vector<std::string> entityFiles;
  static std::vector<YAML::Node> levelNodes;
  dead.clear();
  entityFiles.clear();
  levelNodes.clear();
  
  EntityID nextID = entityMan->getNextID();
  
  for (auto &c : components) {
    c.second->update(delta);
    if (c.second->shouldDestroySelf()) {
      dead.push_back(c.first);
    }
    
    const EntityID numSpawn = c.second->shouldSpawnEntities();
    if (numSpawn != 0) {
      c.second->setFirstID(nextID);
    }
    nextID += numSpawn;
    for (EntityID e = 0; e != numSpawn; ++e) {
      entityFiles.push_back(c.second->getEntityFile(e));
      levelNodes.push_back(c.second->getLevelNode(e));
    }
  }
  
  for (auto id : dead) {
    entityMan->destroy(id);
  }
  for (size_t e = 0; e != entityFiles.size(); ++e) {
    entityMan->create(entityFiles[e], levelNodes[e]);
  }
}
