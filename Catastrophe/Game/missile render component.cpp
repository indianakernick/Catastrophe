//
//  missile render component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "missile render component.hpp"

#include "nanovg.hpp"

void MissileRenderComponent::render(NVGcontext *const ctx) {
  setModelTransform(ctx);
  
  nvgBeginPath(ctx);
  nvgFillColor(ctx, nvgRGBf(0.0f, 1.0f, 0.0f));
  nvgRect(ctx, -0.5f, -0.5f, 0.8f, 1.0f);
  nvgMoveTo(ctx, 0.3f, -0.5f);
  nvgLineTo(ctx, 0.5f, 0.0f);
  nvgLineTo(ctx, 0.3f, 0.5f);
  nvgClosePath(ctx);
  nvgFill(ctx);
}
