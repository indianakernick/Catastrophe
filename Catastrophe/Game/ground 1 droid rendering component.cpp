//
//  ground 1 droid rendering component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 22/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "ground 1 droid rendering component.hpp"

#include "common droid rendering.hpp"
#include "ground droid animation component.hpp"

namespace {
  const NVGcolor BODY_COLOR = nvgRGBf(0.0f, 1.0f, 0.0f);
  const NVGcolor FACE_COLOR = nvgRGBf(0.0f, 0.0f, 0.5f);
  const NVGcolor GUN_COLOR = nvgRGBf(0.1f, 0.1f, 0.1f);
}

void Ground1DroidRenderingComponent::render(NVGcontext *const ctx) {
  const auto animComp = getExpectedCompImpl<const GroundDroidAnimationComponent>();
  
  setModelTransform(ctx);
  
  droidScale(ctx);
  renderGroundDroidLeg(ctx);
  renderGroundDroidWheel(ctx);
  groundDroidBopTranslate(ctx, animComp->getProgress());
  renderGroundDroidBody(ctx, BODY_COLOR);
  renderGroundDroidFace(ctx, FACE_COLOR, animComp->getDir());
  renderGroundDroidGun(ctx, GUN_COLOR, animComp->getGunAngle());
}
