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
#include "yaml helper.hpp"
#include "animation component.hpp"

void ExhaustParticleComponent::init(const YAML::Node &node, Particle *begin) {
  getOptional(color, node, "color");
  getOptional(relPos, node, "exhaust pos");
  getOptional(spread, node, "spread");
  getOptional(size, node, "size");
  
  Particle *const end = begin + GROUP_SIZE;
  for (; begin != end; ++begin) {
    begin->pos = {1000.0f, 1000.0f};
  }
}

void ExhaustParticleComponent::move(float, Particle *begin) {
  static std::mt19937 gen;
  
  begin += currentIndex;
  currentIndex = (currentIndex + PARTICLES_PER_TICK) % GROUP_SIZE;
  Particle *const end = begin + PARTICLES_PER_TICK;
  
  const glm::mat3 modelMat = getExpectedComp<AnimationComponent>()->getModelMat();
  const glm::vec2 absPos = mulPos(modelMat, relPos);
  
  std::normal_distribution<float> distX(absPos.x, spread);
  std::normal_distribution<float> distY(absPos.y, spread);
  
  for (; begin != end; ++begin) {
    begin->pos.x = distX(gen);
    begin->pos.y = distY(gen);
  }
}

void ExhaustParticleComponent::render(NVGcontext *const ctx, const Particle *begin) {
  const Particle *const end = begin + GROUP_SIZE;
  
  nvgBeginPath(ctx);
  nvgFillColor(ctx, color);
  
  for (; begin != end; ++begin) {
    nvgCircle(ctx, begin->pos.x, begin->pos.y, size);
  }
  
  nvgFill(ctx);
}
