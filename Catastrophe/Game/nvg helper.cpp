//
//  nvg helper.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 4/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "nvg helper.hpp"

#include <nanovg/nanovg.h>

void nvgTransform(NVGcontext *context, const glm::mat3 &m) {
  //   [a c e]
  //   [b d f]
  //   [0 0 1]
  //nvgTransform(context, m[0][0], m[1][0], m[0][1], m[1][1], m[0][2], m[1][2]);
  nvgTransform(context, m[0][0], m[0][1], m[1][0], m[1][1], m[2][0], m[2][1]);
}

NVGcolor nvgRGBA(const Color color) {
  return nvgRGBA(color.r, color.g, color.b, color.a);
}
