//
//  missile spawner render component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "missile spawner render component.hpp"

#include "entity.hpp"
#include "nanovg.hpp"
#include "animation component.hpp"

namespace {
  const NVGcolor BARREL = nvgRGBf(0.6f, 0.6f, 0.6f);
  const NVGcolor BASE = nvgRGBf(0.2f, 0.2f, 0.2f);
}

void MissileSpawnerRenderComponent::render(NVGcontext *const ctx) {
  setModelTransform(ctx);
  
  nvgBeginPath(ctx);
  nvgFillColor(ctx, BASE);
  nvgCircle(ctx, 0.0f, 0.0f, 0.25f);
  nvgFill(ctx);
  
  nvgScale(ctx, 1.0f, 0.125f);
  nvgBeginPath(ctx);
  nvgFillColor(ctx, BARREL);
  nvgRect(ctx, -0.5f, -0.5f, 1.0f, 1.0f);
  nvgFill(ctx);
}

AABB MissileSpawnerRenderComponent::getAABB() const {
  const glm::mat3 modelMat = getExpectedComp<AnimationComponent>()->getModelMat();
  return {
    modelMat * glm::vec3(-1.0f, -1.0f, 1.0f),
    modelMat * glm::vec3(1.0f, 1.0f, 1.0f)
  };
}
