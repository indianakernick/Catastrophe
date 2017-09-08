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

StaticColorRenderComponent::StaticColorRenderComponent(
  const NVGcolor color,
  const float width,
  const float height
) : color(color),
    rect(0.0f, 0.0f, width, height) {}

void StaticColorRenderComponent::update(Entity *entity, const float) {
  const b2Vec2 pos = entity->getPos();
  rect.c = {pos.x, pos.y};
}

void StaticColorRenderComponent::render(NVGcontext *context) {
  nvgSave(context);
  
  nvgBeginPath(context);
  nvgFillColor(context, color);
  const Rect rectps = static_cast<Rect>(rect);
  nvgRect(context, rectps.p.x, rectps.p.y, rectps.s.x, rectps.s.y);
  nvgFill(context);
  
  nvgRestore(context);
}

const CameraMotionTarget *StaticColorRenderComponent::getCameraTarget() const {
  return &rect;
}
