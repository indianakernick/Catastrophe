//
//  pentagon render component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 8/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "pentagon render component.hpp"

#include "nvg helper.hpp"
#include <Simpleton/Math/vectors.hpp>

PentagonRenderComponent::PentagonRenderComponent(
  const YAML::Node &node,
  const YAML::Node &level
) : BasicRenderComponent(node, level) {}

namespace {
  glm::vec2 getCirclePoint(const float turn) {
    return Math::angleMag((turn + 0.25) * NVG_PI * 2.0f, 0.5f);
  }
}

void PentagonRenderComponent::render(NVGcontext *const ctx) {
  setModelTransform(ctx);
  
  const float sides = SIDES;
  
  nvgBeginPath(ctx);
  nvgFillColor(ctx, COLOR);
  
  nvgMoveTo(ctx, getCirclePoint(0.0f));
  for (float s = 1.0f; s < sides; ++s) {
    nvgLineTo(ctx, getCirclePoint(s / sides));
  }
  nvgClosePath(ctx);
  
  nvgFill(ctx);
}
