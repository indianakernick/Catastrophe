//
//  particle system.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 3/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "particle system.hpp"

ParticleSystem::ParticleSystem()
  : particles(MAX_PARTICLES),
    effects(MAX_GROUPS) {}

void ParticleSystem::draw(NVGcontext *const context, const float delta) {
  Particle *begin = particles.begin();
  Particle *end = begin + GROUP_SIZE;
  
  for (std::unique_ptr<ParticleEffect> &effect : effects) {
    if (effect) {
      effect->move(delta, begin, end);
      if (!effect->alive()) {
        effect.reset();
      }
    }
    begin = end;
    end += GROUP_SIZE;
  }
  
  begin = particles.begin();
  end = begin + GROUP_SIZE;
  
  for (std::unique_ptr<ParticleEffect> &effect : effects) {
    if (effect) {
      effect->draw(context, begin, end);
    }
    begin = end;
    end += GROUP_SIZE;
  }
}

bool ParticleSystem::createEffect(std::unique_ptr<ParticleEffect> &&effect) {
  for (size_t e = 0; e != effects.size(); ++e) {
    if (!effects[e]) {
      Particle *begin = particles.begin() + e * GROUP_SIZE;
      Particle *end = begin + GROUP_SIZE;
      effect->init(begin, end);
      if (effect->alive()) {
        effects[e] = std::move(effect);
        return true;
      } else {
        break;
      }
    }
  }
  return false;
}
