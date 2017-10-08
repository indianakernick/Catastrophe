//
//  pentagon render component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 8/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "pentagon render component.hpp"

#include <glm/glm.hpp>
#include <Simpleton/Math/vectors.hpp>

PentagonRenderComponent::PentagonRenderComponent(
  const YAML::Node &node,
  const YAML::Node &level
) : BasicRenderComponent(node, level) {}

namespace {
  glm::vec2 getCirclePoint(const float turn) {
    const float rot = 0.25;
    return Math::angleMag((turn + rot) * NVG_PI * 2.0f, 0.5f);
  }
}

void PentagonRenderComponent::render(NVGcontext *const ctx) {
  const float sides = SIDES;
  
  nvgBeginPath(ctx);
  nvgFillColor(ctx, COLOR);
  
  glm::vec2 point = getCirclePoint(0.0f);
  nvgMoveTo(ctx, point.x, point.y);
  for (float s = 1.0f; s < sides; ++s) {
    point = getCirclePoint(s / sides);
    nvgLineTo(ctx, point.x, point.y);
  }
  nvgClosePath(ctx);
  
  nvgFill(ctx);
}
