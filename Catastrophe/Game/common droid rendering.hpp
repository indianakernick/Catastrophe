//
//  common droid rendering.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 22/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef common_droid_rendering_hpp
#define common_droid_rendering_hpp

#include "nanovg.hpp"

const NVGcolor DEFAULT_GROUND_DROID_LEG_COLOR = nvgRGBf(0.3f, 0.3f, 0.3f);
const NVGcolor DEFAULT_GROUND_DROID_WHEEL_COLOR = nvgRGBf(0.1f, 0.1f, 0.1f);

void droidScale(NVGcontext *);
void groundDroidBopTranslate(NVGcontext *, float);
void renderGroundDroidLeg(NVGcontext *, NVGcolor = DEFAULT_GROUND_DROID_LEG_COLOR);
void renderGroundDroidWheel(NVGcontext *, NVGcolor = DEFAULT_GROUND_DROID_WHEEL_COLOR);
void renderGroundDroidBody(NVGcontext *, NVGcolor);
void renderGroundDroidFace(NVGcontext *, NVGcolor, float);
void renderGroundDroidGun(NVGcontext *, NVGcolor, float);

#endif
