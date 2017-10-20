//
//  missile rendering component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "missile rendering component.hpp"

#include "nanovg.hpp"

const NVGcolor BODY = nvgRGBf(0.6f, 0.6f, 0.6f);
const NVGcolor STRIPES = nvgRGBf(1.0f, 0.0f, 0.0f);
const NVGcolor EXHAUST = nvgRGBf(1.0f, 0.51f, 0.0f);

void MissileRenderingComponent::body(NVGcontext *const ctx) {
  nvgBeginPath(ctx);
  nvgFillColor(ctx, BODY);
  nvgMoveTo(ctx, 0.5f, 0.0f);
  nvgLineTo(ctx, 0.3f, -0.5f);
  nvgLineTo(ctx, -0.5f, -0.5f);
  nvgLineTo(ctx, -0.5f, 0.5f);
  nvgLineTo(ctx, 0.3f, 0.5f);
  nvgLineTo(ctx, 0.5f, 0.0f);
  nvgFill(ctx);
}

void MissileRenderingComponent::fins(NVGcontext *const ctx) {
  nvgBeginPath(ctx);
  nvgFillColor(ctx, BODY);
  
  //back left
  nvgMoveTo(ctx, -0.4f, 0.0f);
  nvgLineTo(ctx, -0.5f, 2.0f);
  nvgLineTo(ctx, -0.4f, 2.0f);
  nvgLineTo(ctx, -0.25f, 0.0f);
  //back right
  nvgLineTo(ctx, -0.4f, -2.0f);
  nvgLineTo(ctx, -0.5f, -2.0f);
  nvgLineTo(ctx, -0.4f, 0.0f);
  nvgFill(ctx);
}

void MissileRenderingComponent::stripes(NVGcontext *const ctx) {
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

void MissileRenderingComponent::exhaust(NVGcontext *const ctx) {
  nvgBeginPath(ctx);
  
  nvgBeginPath(ctx);
  nvgFillColor(ctx, EXHAUST);
  nvgMoveTo(ctx, -0.6f, 0.0f);
  nvgLineTo(ctx, -0.5f, -0.5f);
  nvgLineTo(ctx, -0.5f, 0.5f);
  nvgClosePath(ctx);
  nvgFill(ctx);
}

void MissileRenderingComponent::render(NVGcontext *const ctx) {
  setModelTransform(ctx);
  
  fins(ctx);
  exhaust(ctx);
  body(ctx);
  stripes(ctx);
}
