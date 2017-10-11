//
//  ground drone render component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 11/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "ground drone render component.hpp"

#include "nanovg.hpp"

void GroundDroneRenderComponent::render(NVGcontext *const ctx) {
  setModelTransform(ctx);
  
  nvgBeginPath(ctx);
  nvgFillColor(ctx, nvgRGBf(1.0f, 0.0f, 0.0f));
  nvgRect(ctx, -0.5f, -0.5f, 1.0f, 1.0f);
  nvgFill(ctx);
}
