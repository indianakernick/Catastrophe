//
//  particle system.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 3/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "particle system.hpp"

#include "particle component.hpp"

void ParticleSystem::init() {
  particles.emplace(NUM_GROUPS);
}

void ParticleSystem::quit() {
  particles = std::experimental::nullopt;
}

void ParticleSystem::add(
  const EntityID id,
  const CompPtr comp,
  const YAML::Node &node
) {
  const CompData compData = {
    comp,
    particles->alloc()
  };
  components.emplace(id, compData);
  comp->init(node, compData.firstParticle);
}

void ParticleSystem::rem(const EntityID id) {
  const auto iter = components.find(id);
  if (iter != components.end()) {
    particles->free(iter->second.firstParticle);
    components.erase(iter);
  }
}

void ParticleSystem::render(NVGcontext *const ctx, const float delta) {
  for (auto &c : components) {
    Particle *const firstParticle = c.second.firstParticle;
    c.second.comp->move(delta, firstParticle);
    c.second.comp->render(ctx, firstParticle);
  }
}
