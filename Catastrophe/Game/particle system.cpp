//
//  particle system.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 3/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "particle system.hpp"

#include "layer names.hpp"
#include "global flags.hpp"
#include "rendering manager.hpp"
#include "rendering context.hpp"
#include "particle component.hpp"
#include <Simpleton/Utils/profiler.hpp>

void ParticleSystem::init(RenderingManager &newRenderingMan) {
  assert(renderingMan == nullptr);
  renderingMan = &newRenderingMan;
  particles.emplace(NUM_GROUPS);
  const size_t numLayers = getNumLayers();
  layers.reserve(numLayers);
  for (size_t l = 0; l != numLayers; ++l) {
    layers.push_back(std::make_shared<Layer>());
    renderingMan->addJob(l, layers.back());
  }
}

void ParticleSystem::quit() {
  assert(renderingMan);
  for (auto &layer : layers) {
    for (auto &pair : layer->comps) {
      particles->free(pair.second.firstParticle);
    }
    layer->kill();
  }
  layers.clear();
  particles = std::experimental::nullopt;
  renderingMan = nullptr;
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
  comp->init(node, compData.firstParticle);
  const size_t layer = comp->getLayer();
  if (layer >= layers.size()) {
    throw std::range_error("Layer index out of range");
  }
  layers[layer]->comps.emplace(id, compData);
}

void ParticleSystem::rem(const EntityID id) {
  for (auto &layer : layers) {
    auto &comps = layer->comps;
    auto iter = comps.find(id);
    if (iter != comps.end()) {
      particles->free(iter->second.firstParticle);
      comps.erase(iter);
    }
  }
}

void ParticleSystem::update(const float delta) {
  PROFILE(ParticleSystem update);
  
  for (auto &layer : layers) {
    for (auto &pair : layer->comps) {
      Particle *const firstParticle = pair.second.firstParticle;
      pair.second.comp->move(delta, firstParticle);
    }
  }
}

void ParticleSystem::Layer::render(RenderingContext &renderer) {
  if constexpr (ENABLE_PARTICLE_RENDER) {
    PROFILE(ParticleSystem render);
    
    NVGcontext *const ctx = renderer.getContext();
    for (auto &pair : comps) {
      Particle *const firstParticle = pair.second.firstParticle;
      pair.second.comp->render(ctx, firstParticle);
    }
  }
}
