//
//  spikes render component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 8/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "spikes render component.hpp"

void SpikesRenderComponent::render(NVGcontext *const ctx) {
  setModelTransform(ctx);
  
  const NVGpaint gradient = nvgLinearGradient(ctx,
    -4.0f, 0.0f,
    -4.0f + SPIKE_WIDTH, 0.0f,
    LEFT_COLOR,
    RIGHT_COLOR
  );
  
  nvgScale(ctx, 0.125f, 0.125f);
  
  for (int s = 0; s != NUM_SPIKES; ++s) {
    nvgBeginPath(ctx);
    nvgFillPaint(ctx, gradient);
    nvgMoveTo(ctx, -4.0f, -4.0f);
    nvgLineTo(ctx, -4.0f + HALF_SPIKE_WIDTH, -4.0f + SPIKE_HEIGHT);
    nvgLineTo(ctx, -4.0f + SPIKE_WIDTH, -4.0f);
    nvgClosePath(ctx);
    nvgFill(ctx);
    
    nvgTranslate(ctx, SPIKE_WIDTH, 0.0f);
  }
}
