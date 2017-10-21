//
//  animation system.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "animation system.hpp"

#include "animation component.hpp"
#include <Simpleton/Utils/profiler.hpp>

void AnimationSystem::add(
  const EntityID entityID,
  const CompPtr comp,
  const YAML::Node &node
) {
  comp->init(node);
  components.emplace(entityID, comp);
}

void AnimationSystem::rem(const EntityID entityID) {
  components.erase(entityID);
}

void AnimationSystem::update(const float delta) {
  PROFILE(AnimationSystem update);
 
  for (auto c = components.cbegin(); c != components.cend(); ++c) {
    c->second->update(delta);
  }
}
