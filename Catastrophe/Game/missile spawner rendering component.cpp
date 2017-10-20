//
//  missile spawner rendering component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "missile spawner rendering component.hpp"

#include "entity.hpp"
#include "nanovg.hpp"
#include "matrix mul.hpp"
#include "animation component.hpp"

namespace {
  const NVGcolor BARREL = nvgRGBf(0.6f, 0.6f, 0.6f);
  const NVGcolor BASE = nvgRGBf(0.2f, 0.2f, 0.2f);
}

void MissileSpawnerRenderingComponent::render(NVGcontext *const ctx) {
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

AABB MissileSpawnerRenderingComponent::getAABB() const {
  const glm::mat3 modelMat = getExpectedComp<AnimationComponent>()->getModelMat();
  return {
    mulPos(modelMat, {-1.0f, -1.0f}),
    mulPos(modelMat, {1.0f, 1.0f})
  };
}
