//
//  ground 0 droid rendering component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "ground 0 droid rendering component.hpp"

#include "common droid rendering.hpp"
#include "ground droid animation component.hpp"

namespace {
  const NVGcolor BODY_COLOR = nvgRGBf(1.0f, 0.0f, 0.0f);
  const NVGcolor FACE_COLOR = nvgRGBf(0.0f, 0.0f, 0.5f);
}

void Ground0DroidRenderingComponent::render(NVGcontext *const ctx) {
  const auto animComp = getExpectedCompImpl<GroundDroidAnimationComponent>();
  
  setModelTransform(ctx);
  
  droidScale(ctx);
  renderGroundDroidLeg(ctx, DEFAULT_GROUND_DROID_LEG_COLOR);
  renderGroundDroidWheel(ctx, DEFAULT_GROUND_DROID_WHEEL_COLOR);
  groundDroidBopTranslate(ctx, animComp->getProgress());
  renderGroundDroidBody(ctx, BODY_COLOR);
  renderGroundDroidFace(ctx, FACE_COLOR, animComp->getDir());
}
