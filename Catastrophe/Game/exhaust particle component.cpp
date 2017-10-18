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
  getOptional(subGroupSize, node, "particles per tick");
  groupSize = GROUP_SIZE - GROUP_SIZE % subGroupSize;
  if (const YAML::Node &layerNode = node["layer"]) {
    layer = getLayerIndex(layerNode.Scalar());
  }
  getOptional(lifetime, node, "lifetime");
  
  Particle *const end = begin + GROUP_SIZE;
  for (; begin != end; ++begin) {
    begin->pos = {1000.0f, 1000.0f};
  }
}

void ExhaustParticleComponent::move(const float delta, Particle *begin) {
  freqLimiter.advance(delta);
  auto numTicks = freqLimiter.canDoMultipleOverlap();
  while (numTicks--) {
    updateTick(begin);
  }
  Particle *const end = begin + groupSize;
  for (; begin != end; begin += subGroupSize) {
    //the first particle in each sub group stores the lifetime
    begin->data.f[0] = std::max(0.0f, begin->data.f[0] - delta);
  }
}

void ExhaustParticleComponent::render(NVGcontext *const ctx, const Particle *begin) {
  const Particle *const end = begin + groupSize;
  while (begin != end) {
    nvgBeginPath(ctx);
    NVGcolor groupColor = color;
    //the first particle in each sub group stores the lifetime
    groupColor.a *= begin->data.f[0];
    nvgFillColor(ctx, groupColor);
    const Particle *const groupEnd = begin + subGroupSize;
    for (; begin != groupEnd; ++begin) {
      nvgCircle(ctx, begin->pos.x, begin->pos.y, size);
    }
    nvgFill(ctx);
  }
}

size_t ExhaustParticleComponent::getLayer() const {
  return layer;
}

void ExhaustParticleComponent::updateTick(Particle *const begin) {
  static std::mt19937 gen;
  
  Particle *const subGroupBegin = begin + oldestSubGroupIndex;
  oldestSubGroupIndex = (oldestSubGroupIndex + subGroupSize) % groupSize;
  Particle *const subGroupEnd = subGroupBegin + subGroupSize;

  const glm::mat3 modelMat = getExpectedComp<AnimationComponent>()->getModelMat();
  const glm::vec2 absPos = mulPos(modelMat, relPos);

  std::normal_distribution<float> distX(absPos.x, spread);
  std::normal_distribution<float> distY(absPos.y, spread);

  //All particles in a subgroup have the same lifetime
  subGroupBegin->data.f[0] = lifetime;
  for (Particle *p = subGroupBegin; p != subGroupEnd; ++p) {
    p->pos.x = distX(gen);
    p->pos.y = distY(gen);
  }
}
