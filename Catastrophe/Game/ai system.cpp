//
//  ai system.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "ai system.hpp"

#include "ai component.hpp"
#include <Simpleton/Utils/profiler.hpp>

void AISystem::add(
  const EntityID id,
  const CompPtr comp,
  const YAML::Node &node
) {
  comp->init(node);
  components.emplace(id, comp);
}

void AISystem::rem(const EntityID id) {
  components.erase(id);
}

void AISystem::update(const float delta) {
  PROFILE(AISystem update);
  
  for (auto &pair : components) {
    pair.second->update(delta);
  }
}
