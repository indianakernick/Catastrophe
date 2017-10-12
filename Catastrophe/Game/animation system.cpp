//
//  animation system.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "animation system.hpp"

#include "animation component.hpp"

void AnimationSystem::add(
  const EntityID entityID,
  const CompPtr comp,
  const YAML::Node &node
) {
  components.emplace(entityID, comp);
  comp->init(node);
}

void AnimationSystem::rem(const EntityID entityID) {
  components.erase(entityID);
}

void AnimationSystem::update(const float delta) {
  for (auto c = components.cbegin(); c != components.cend(); ++c) {
    c->second->update(delta);
  }
}
