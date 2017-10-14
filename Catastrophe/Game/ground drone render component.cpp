//
//  ground drone render component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 11/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "ground drone render component.hpp"

const NVGcolor GroundDroneRenderComponent::OUTLINE = nvgRGBf(1.0f, 0.0f, 0.0f);
const NVGcolor GroundDroneRenderComponent::FILL = nvgRGBf(0.1f, 0.1f, 0.5f);

void GroundDroneRenderComponent::render(NVGcontext *const ctx) {
  setModelTransform(ctx);
  
  nvgBeginPath(ctx);
  nvgFillColor(ctx, FILL);
  nvgRect(ctx, -0.5f, -0.5f, 1.0f, 1.0f);
  nvgFill(ctx);
  
  nvgScissor(ctx, -0.5f, -0.5f, 1.0f, 1.0f);
  nvgStrokeColor(ctx, OUTLINE);
  nvgStrokeWidth(ctx, 0.2f);
  
  //outside
  nvgBeginPath(ctx);
  nvgMoveTo(ctx, -0.5f, -0.5f);
  nvgLineTo(ctx, -0.5f, 0.5f);
  nvgLineTo(ctx, 0.5f, 0.5f);
  nvgLineTo(ctx, 0.5f, -0.5f);
  nvgStroke(ctx);
  
  nvgResetScissor(ctx);
  nvgStrokeWidth(ctx, 0.1f);
  
  //mouth
  nvgBeginPath(ctx);
  nvgMoveTo(ctx, -0.3f, -0.2f);
  nvgLineTo(ctx, 0.3f, -0.2f);
  nvgStroke(ctx);
  
  nvgFillColor(ctx, OUTLINE);
  
  //eyes
  nvgBeginPath(ctx);
  nvgCircle(ctx, -0.2f, 0.2f, 0.1f);
  nvgCircle(ctx, 0.2f, 0.2f, 0.1f);
  nvgFill(ctx);
}
