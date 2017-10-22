//
//  droid bullet rendering component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 22/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "droid bullet rendering component.hpp"

#include "nanovg.hpp"

namespace {
  const NVGcolor COLOR = nvgRGBf(0.2f, 0.2f, 0.2f);
}

void DroidBulletRenderingComponent::render(NVGcontext *const ctx) {
  setModelTransform(ctx);
  
  nvgBeginPath(ctx);
  nvgFillColor(ctx, COLOR);
  nvgCircle(ctx, 0.0f, 0.0f, 0.5f);
  nvgFill(ctx);
}
