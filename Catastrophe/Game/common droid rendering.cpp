//
//  common droid rendering.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 22/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "common droid rendering.hpp"

#include <cmath>
#include <Simpleton/Math/clamp.hpp>

namespace {
  NVGcolor brighten(const NVGcolor color) {
    constexpr float DELTA = 0.1f;
  
    NVGcolor newColor;
    newColor.r = Math::clampMax(color.r + DELTA, 1.0f);
    newColor.g = Math::clampMax(color.g + DELTA, 1.0f);
    newColor.b = Math::clampMax(color.b + DELTA, 1.0f);
    newColor.a = color.a;
    return newColor;
  }
  
  NVGcolor darken(const NVGcolor color) {
    constexpr float DELTA = 0.5f;
  
    NVGcolor newColor;
    newColor.r = Math::clampMin(color.r - DELTA, 0.0f);
    newColor.g = Math::clampMin(color.g - DELTA, 0.0f);
    newColor.b = Math::clampMin(color.b - DELTA, 0.0f);
    newColor.a = color.a;
    return newColor;
  }
}

void droidScale(NVGcontext *const ctx) {
  nvgScale(ctx, 0.0625f, 0.0625f); //  1/16
}

void groundDroidBopTranslate(NVGcontext *const ctx, const float progress) {
  nvgTranslate(ctx,
    0.0f,
    (std::sin(progress * 2.0f * NVG_PI) - 1.0f) * 0.5f
  );
}

void renderGroundDroidLeg(NVGcontext *const ctx, const NVGcolor color) {
  nvgBeginPath(ctx);
  nvgStrokeColor(ctx, color);
  nvgStrokeWidth(ctx, 1.0f);
  nvgMoveTo(ctx, 0.0f, -2.0f);
  nvgLineTo(ctx, 0.0f, -7.0f);
  nvgStroke(ctx);
}

void renderGroundDroidWheel(NVGcontext *const ctx, const NVGcolor color) {
  nvgBeginPath(ctx);
  nvgFillColor(ctx, color);
  nvgCircle(ctx, 0.0f, -7.0f, 1.0f);
  nvgFill(ctx);
}

void renderGroundDroidBody(NVGcontext *const ctx, const NVGcolor color) {
  const NVGpaint paint = nvgLinearGradient(
    ctx,
    -2.0f, 0.0f,
    2.0f, 0.0f,
    brighten(color),
    darken(color)
  );
  
  nvgBeginPath(ctx);
  nvgFillPaint(ctx, paint);
  nvgCircle(ctx, 0.0f, 6.0f, 2.0f);
  nvgCircle(ctx, 0.0f, -2.0f, 2.0f);
  nvgRect(ctx, -2.0f, -2.0f, 4.0f, 8.0f);
  nvgFill(ctx);
}

void renderGroundDroidFace(NVGcontext *const ctx, const NVGcolor color, const float dir) {
  nvgScale(ctx, dir, 1.0f);
  
  nvgBeginPath(ctx);
  nvgStrokeColor(ctx, color);
  nvgLineCap(ctx, NVG_BUTT);
  nvgStrokeWidth(ctx, 0.5f);
  nvgMoveTo(ctx, 2.0f, 3.0f);
  nvgLineTo(ctx, 0.5f, 3.0f);
  nvgStroke(ctx);
  
  nvgBeginPath(ctx);
  nvgFillColor(ctx, color);
  nvgCircle(ctx, 1.0f, 5.0f, 0.25f);
  nvgFill(ctx);
  
  //revert scale
  nvgScale(ctx, dir, 1.0f);
}

void renderGroundDroidGun(NVGcontext *const ctx, const NVGcolor color, const float angle) {
  nvgRotate(ctx, angle);
  
  nvgBeginPath(ctx);
  nvgFillColor(ctx, color);
  nvgCircle(ctx, 0.0f, 0.0f, 1.0f);
  nvgRect(ctx, 0.0f, -1.0f, 6.0f, 2.0f);
  nvgFill(ctx);
  
  //revert angle
  nvgRotate(ctx, -angle);
}
