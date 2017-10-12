//
//  launcher render component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 8/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "launcher render component.hpp"

#include "entity.hpp"
#include "launcher animation component.hpp"
#include <Simpleton/Utils/safe down cast.hpp>

void LauncherRenderComponent::render(NVGcontext *const ctx) {
  setModelTransform(ctx);
  
  const auto animComp = Utils::safeDownCast<LauncherAnimationComponent>(
    getEntity().get<AnimationComponent>()
  );
  const float progress = animComp->getProgress();
  const float armHeight = progress / NUM_LEVELS;
  const float armWidth = std::sqrt(2.0f * MAX_ARM_HEIGHT_2 - armHeight * armHeight);
  const float armX = armWidth / 2.0f;
  
  nvgTranslate(ctx, 0.0f, -0.5f);
  nvgScissor(ctx, -0.5f, 0.0f, 1.0f, progress);
  nvgLineJoin(ctx, NVG_ROUND);
  nvgLineCap(ctx, NVG_ROUND);
  nvgStrokeWidth(ctx, ARM_THICKNESS);
  nvgStrokeColor(ctx, ARM_COLOR);
  
  const auto drawArms = [armX, armHeight] (NVGcontext *ctx, float side) {
    nvgMoveTo(ctx, armX * side, 0.0f);
    for (float y = 1.0f; y <= NUM_LEVELS; ++y) {
      side = -side;
      nvgLineTo(ctx, armX * side, y * armHeight);
    }
  };
  nvgBeginPath(ctx);
  drawArms(ctx, 1.0f);
  drawArms(ctx, -1.0f);
  nvgStroke(ctx);
  
  nvgBeginPath(ctx);
  nvgFillColor(ctx, HINGE_COLOR);
  for (float y = 0.0f; y <= NUM_LEVELS; ++y) {
    nvgCircle(ctx, armX, y * armHeight, HINGE_RADIUS);
    nvgCircle(ctx, -armX, y * armHeight, HINGE_RADIUS);
  }
  for (float y = 0.0f; y < NUM_LEVELS; ++y) {
    nvgCircle(ctx, 0.0f, y * armHeight + armHeight / 2.0f, HINGE_RADIUS);
  }
  nvgFill(ctx);
}
