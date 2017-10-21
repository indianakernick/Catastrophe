//
//  ground 0 droid rendering component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "ground 0 droid rendering component.hpp"

#include "nanovg.hpp"
#include "ground droid animation component.hpp"

void Ground0DroidRenderingComponent::render(NVGcontext *const ctx) {
  const auto animComp = getExpectedCompImpl<GroundDroidAnimationComponent>();
  
  setModelTransform(ctx);
  
  nvgScale(ctx, 0.0625f, 0.0625f);
  
  renderLeg(ctx);
  renderWheel(ctx);

  nvgTranslate(ctx,
    0.0f,
    (std::sin(animComp->getProgress() * 2.0f * NVG_PI) - 1.0f) * 0.5f
  );
  
  renderBody(ctx);
  renderFace(ctx, animComp->getDir());
  
  nvgRestore(ctx);
}

void Ground0DroidRenderingComponent::renderLeg(NVGcontext *const ctx) {
  nvgBeginPath(ctx);
  nvgStrokeColor(ctx, nvgRGBf(0.3f, 0.3f, 0.3f));
  nvgStrokeWidth(ctx, 1.0f);
  nvgMoveTo(ctx, 0.0f, -2.0f);
  nvgLineTo(ctx, 0.0f, -7.0f);
  nvgStroke(ctx);
}

void Ground0DroidRenderingComponent::renderWheel(NVGcontext *const ctx) {
  nvgBeginPath(ctx);
  nvgFillColor(ctx, nvgRGBf(0.1f, 0.1f, 0.1f));
  nvgCircle(ctx, 0.0f, -7.0f, 1.0f);
  nvgFill(ctx);
}

void Ground0DroidRenderingComponent::renderBody(NVGcontext *const ctx) {
  NVGpaint paint = nvgLinearGradient(
    ctx,
    -2.0f, 0.0f,
    2.0f, 0.0f,
    nvgRGBf(1.0f, 0.125f, 0.125f),
    nvgRGBf(0.5f, 0.0f, 0.0f)
  );
  
  nvgBeginPath(ctx);
  nvgFillPaint(ctx, paint);
  nvgCircle(ctx, 0.0f, 6.0f, 2.0f);
  nvgCircle(ctx, 0.0f, -2.0f, 2.0f);
  nvgRect(ctx, -2.0f, -2.0f, 4.0f, 8.0f);
  nvgFill(ctx);
}

void Ground0DroidRenderingComponent::renderFace(NVGcontext *const ctx, const float dir) {
  nvgScale(ctx, dir, 1.0f);
  
  nvgBeginPath(ctx);
  nvgStrokeColor(ctx, nvgRGBf(0.0f, 0.0f, 0.5f));
  nvgLineCap(ctx, NVG_BUTT);
  nvgStrokeWidth(ctx, 0.5f);
  nvgMoveTo(ctx, 2.0f, 3.0f);
  nvgLineTo(ctx, 0.5f, 3.0f);
  nvgStroke(ctx);
  
  nvgBeginPath(ctx);
  nvgFillColor(ctx, nvgRGBf(0.0f, 0.0f, 0.5f));
  nvgCircle(ctx, 1.0f, 5.0f, 0.25f);
  nvgFill(ctx);
}
