//
//  polygon render component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 8/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "polygon render component.hpp"

#include "entity.hpp"
#include "nvg helper.hpp"
#include "yaml helper.hpp"
#include "animation component.hpp"
#include <Simpleton/Math/vectors.hpp>

PolygonRenderComponent::PolygonRenderComponent(
  const YAML::Node &node,
  const YAML::Node &level
) : BasicRenderComponent(node, level) {
  getOptional(numSides, node, level, "sides");
  getOptional(color, node, level, "color");
  getOptional(rotPerSecond, node, level, "rotations per second");
  getOptional(rotationOffset, node, level, "rotation");
}

void PolygonRenderComponent::render(NVGcontext *const ctx) {
  setModelTransform(ctx);
  
  if (rotPerSecond != 0.0f) {
    const float progress = getEntity().animation->getProgress();
    rotation = progress * rotPerSecond;
  }
  
  const float sides = numSides;
  
  nvgBeginPath(ctx);
  nvgFillColor(ctx, color);
  
  nvgMoveTo(ctx, getCirclePoint(0.0f));
  for (float s = 1.0f; s < sides; ++s) {
    nvgLineTo(ctx, getCirclePoint(s / sides));
  }
  nvgClosePath(ctx);
  
  nvgFill(ctx);
}

glm::vec2 PolygonRenderComponent::getCirclePoint(const float turn) const {
  return Math::angleMag((turn + rotation + rotationOffset) * NVG_PI * 2.0f, 0.5f);
}
