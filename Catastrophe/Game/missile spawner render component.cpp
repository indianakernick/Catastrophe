//
//  missile spawner render component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "missile spawner render component.hpp"

#include "nanovg.hpp"

void MissileSpawnerRenderComponent::render(NVGcontext *const ctx) {
  setModelTransform(ctx);
  
  nvgBeginPath(ctx);
  nvgFillColor(ctx, nvgRGBf(0.0f, 0.0f, 1.0f));
  nvgCircle(ctx, 0.0f, 0.0f, 0.5f);
  nvgFill(ctx);
}
