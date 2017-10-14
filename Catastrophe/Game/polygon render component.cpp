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

void PolygonRenderComponent::init(RenderingContext &renderer, const YAML::Node &node) {
  BasicRenderComponent::init(renderer, node);
  getOptional(numSides, node, "sides");
  getOptional(color, node, "color");
  getOptional(rotPerSecond, node, "rotations per second");
  getOptional(rotationOffset, node, "rotation");
}

void PolygonRenderComponent::render(NVGcontext *const ctx) {
  setModelTransform(ctx);
  
  if (rotPerSecond != 0.0f) {
    const float progress = getExpectedComp<AnimationComponent>()->getProgress();
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
