//
//  animation system.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "animation system.hpp"

#include "entity manager.hpp"
#include "animation component.hpp"

void AnimationSystem::add(
  const EntityID entityID,
  const std::shared_ptr<AnimationComponent> comp
) {
  components.emplace(entityID, comp);
}

void AnimationSystem::rem(const EntityID entityID) {
  components.erase(entityID);
}

void AnimationSystem::update(EntityManager &entityMan, const float delta) {
  for (auto c = components.cbegin(); c != components.cend(); ++c) {
    const Entity &entity = entityMan.getEntity(c->first);
    const PhysicsState &physics = *entity.latestPhysicsState;
    RenderingState &rendering = *entity.latestRenderingState;
    c->second->update(rendering, physics, delta);
  }
}
