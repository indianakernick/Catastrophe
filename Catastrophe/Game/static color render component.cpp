//
//  static color render component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "static color render component.hpp"

#include "rect.hpp"
#include "entity.hpp"
#include <nanovg/nanovg.h>
#include "rendering state.hpp"

StaticColorRenderComponent::StaticColorRenderComponent(
  const NVGcolor color,
  const float width,
  const float height
) : color(color),
    rect(0.0f, 0.0f, width, height),
    size(width, height) {}

void StaticColorRenderComponent::render(
  NVGcontext *context,
  const RenderingState &rendering
) {
  rect.c = rendering.modelMat[2];

  nvgSave(context);
  
  nvgBeginPath(context);
  nvgFillColor(context, color);
  const Rect rectps = static_cast<Rect>(rect);
  nvgRect(context, rectps.p.x, rectps.p.y, rectps.s.x, rectps.s.y);
  nvgFill(context);
  
  nvgRestore(context);
}

const CameraMotionTarget *StaticColorRenderComponent::getMotionTarget() const {
  return &rect;
}

const CameraZoomTarget *StaticColorRenderComponent::getZoomTarget() const {
  return &size;
}

Rect StaticColorRenderComponent::getAABB(const RenderingState &) const {
  return static_cast<Rect>(rect);
}
