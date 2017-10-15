//
//  particle system.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 3/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "particle system.hpp"

ParticleSystem::ParticleSystem()
  : particles(GROUPS) {}

void ParticleSystem::draw(NVGcontext *const context, const float delta) {
  effects.remove_if([this, delta] (const EffectData &effect) {
    effect.effect->move(delta, effect.firstParticle, effect.firstParticle + GROUP_SIZE);
    if (!effect.effect->alive()) {
      particles.free(effect.firstParticle);
      return true;
    } else {
      return false;
    }
  });
  
  for (auto &e : effects) {
    e.effect->draw(context, e.firstParticle, e.firstParticle + GROUP_SIZE);
  }
}

bool ParticleSystem::createEffect(std::unique_ptr<ParticleEffect> &&effect) {
  Particle *particleGroup;
  try {
    particleGroup = particles.alloc();
  } catch (std::bad_alloc &) {
    return false;
  }
  effect->init(particleGroup, particleGroup + GROUP_SIZE);
  if (effect->alive()) {
    effects.push_front({std::move(effect), particleGroup});
    return true;
  } else {
    return false;
  }
}
