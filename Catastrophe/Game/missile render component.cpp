//
//  missile render component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "missile render component.hpp"

#include "nanovg.hpp"

const NVGcolor MissileRenderComponent::INNER_BODY = nvgRGBf(0.6f, 0.6f, 0.6f);
const NVGcolor MissileRenderComponent::OUTER_BODY = nvgRGBf(0.3f, 0.3f, 0.3f);
const NVGcolor MissileRenderComponent::STRIPES = nvgRGBf(1.0f, 0.0f, 0.0f);
const NVGcolor MissileRenderComponent::EXHAUST = nvgRGBf(1.0f, 0.51f, 0.0f);

void MissileRenderComponent::leftBody(NVGcontext *const ctx) {
  const NVGpaint gradient = nvgLinearGradient(ctx,
    0.0f, 0.0f,
    0.0f, 0.4f,
    INNER_BODY,
    OUTER_BODY
  );
  
  //The scissor rectangle drops down a bit to cover up the tiny cap between
  //the two sides of the body that sometimes appears.
  nvgScissor(ctx, -0.5f, -0.1f, 1.0f, 8.0f);
  
  nvgBeginPath(ctx);
  nvgFillPaint(ctx, gradient);
  nvgRect(ctx, -0.5f, 0.0f, 0.8f, 0.5f);
  nvgEllipse(ctx, 0.3f, 0.0f, 0.2f, 0.5f);
  nvgFill(ctx);
}

void MissileRenderComponent::body(NVGcontext *const ctx) {
  leftBody(ctx);
  nvgScale(ctx, 1.0f, -1.0f);
  leftBody(ctx);
  nvgScale(ctx, 1.0f, -1.0f);
  nvgResetScissor(ctx);
}

void MissileRenderComponent::fins(NVGcontext *const ctx) {
  nvgBeginPath(ctx);
  nvgFillColor(ctx, OUTER_BODY);
  
  //back left
  nvgMoveTo(ctx, -0.4f, 0.0f);
  nvgLineTo(ctx, -0.5f, 2.0f);
  nvgLineTo(ctx, -0.4f, 2.0f);
  nvgLineTo(ctx, -0.25f, 0.0f);
  //back right
  nvgLineTo(ctx, -0.4f, -2.0f);
  nvgLineTo(ctx, -0.5f, -2.0f);
  nvgLineTo(ctx, -0.4f, 0.0f);
  
  //front
  nvgMoveTo(ctx, 0.2f, 1.25f);
  nvgLineTo(ctx, 0.3f, 0.0f);
  nvgLineTo(ctx, 0.2f, -1.25f);
  nvgClosePath(ctx);
  nvgFill(ctx);
}

void MissileRenderComponent::stripes(NVGcontext *const ctx) {
  nvgBeginPath(ctx);
  nvgStrokeColor(ctx, STRIPES);
  nvgStrokeWidth(ctx, 0.05f);
  
  nvgMoveTo(ctx, -0.3f, -0.5f);
  nvgLineTo(ctx, -0.3f, 0.5f);
  
  nvgMoveTo(ctx, -0.1f, -0.5f);
  nvgLineTo(ctx, -0.1f, 0.5f);
  
  nvgMoveTo(ctx, 0.1f, -0.5f);
  nvgLineTo(ctx, 0.1f, 0.5f);
  
  nvgMoveTo(ctx, 0.3f, -0.5f);
  nvgLineTo(ctx, 0.3f, 0.5f);
  
  nvgStroke(ctx);
}

void MissileRenderComponent::exhaust(NVGcontext *const ctx) {
  nvgBeginPath(ctx);
  
  const NVGpaint gradient = nvgRadialGradient(ctx,
    -0.5f, 0.0f,
    0.1f,
    0.2f,
    EXHAUST,
    nvgTransRGBAf(EXHAUST, 0.25f)
  );
  
  nvgBeginPath(ctx);
  nvgFillPaint(ctx, gradient);
  nvgEllipse(ctx, -0.55f, 0.0f, 0.125f, 0.5f);
  nvgFill(ctx);
}

void MissileRenderComponent::render(NVGcontext *const ctx) {
  setModelTransform(ctx);
  
  fins(ctx);
  exhaust(ctx);
  body(ctx);
  stripes(ctx);
}
