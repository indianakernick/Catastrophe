//
//  exhaust particle component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 16/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "exhaust particle component.hpp"

#include <random>
#include "nanovg.hpp"
#include "matrix mul.hpp"
#include "layer names.hpp"
#include "yaml helper.hpp"
#include "animation component.hpp"

void ExhaustParticleComponent::init(const YAML::Node &node, Particle *begin) {
  getOptional(color, node, "color");
  getOptional(relPos, node, "exhaust pos");
  getOptional(spread, node, "spread");
  getOptional(size, node, "size");
  float ticksPerSecond = 60.0f;
  getOptional(ticksPerSecond, node, "ticks per second");
  freqLimiter.setFrequency(ticksPerSecond);
  getOptional(particlesPerTick, node, "particles per tick");
  usedGroupSize = GROUP_SIZE - GROUP_SIZE % particlesPerTick;
  if (const YAML::Node &layerNode = node["layer"]) {
    layer = getLayerIndex(layerNode.Scalar());
  }
  getOptional(lifetime, node, "lifetime");
  
  Particle *const end = begin + GROUP_SIZE;
  for (; begin != end; ++begin) {
    begin->pos = {1000.0f, 1000.0f};
  }
}

void ExhaustParticleComponent::move(const float delta, Particle *const begin) {
  //@TODO tidy this up
  
  static std::mt19937 gen;
  
  freqLimiter.advance(delta);
  auto numTicks = freqLimiter.canDoMultipleOverlap();
  
  for (Particle *p = begin + currentIndex; numTicks--; p += particlesPerTick) {
    currentIndex = (currentIndex + particlesPerTick) % usedGroupSize;
    Particle *const end = p + particlesPerTick;
    
    const glm::mat3 modelMat = getExpectedComp<AnimationComponent>()->getModelMat();
    const glm::vec2 absPos = mulPos(modelMat, relPos);
    
    std::normal_distribution<float> distX(absPos.x, spread);
    std::normal_distribution<float> distY(absPos.y, spread);
    
    for (Particle *q = p; q != end; ++q) {
      q->pos.x = distX(gen);
      q->pos.y = distY(gen);
      q->data.f[0] = lifetime;
    }
  }
  
  for (Particle *p = begin; p != begin + usedGroupSize; ++p) {
    p->data.f[0] = std::max(0.0f, p->data.f[0] - delta);
  }
}

void ExhaustParticleComponent::render(NVGcontext *const ctx, const Particle *begin) {
  const Particle *const end = begin + usedGroupSize;
  
  //@TODO
  //All circles that were created during the same tick will have the same color
  //So many circles can be filled at once
  for (; begin != end; ++begin) {
    nvgBeginPath(ctx);
    NVGcolor thisColor = color;
    thisColor.a *= begin->data.f[0];
    nvgFillColor(ctx, thisColor);
    nvgCircle(ctx, begin->pos.x, begin->pos.y, size);
    nvgFill(ctx);
  }
}

size_t ExhaustParticleComponent::getLayer() const {
  return layer;
}
