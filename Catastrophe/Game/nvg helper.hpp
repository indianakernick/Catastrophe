//
//  nvg helper.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 4/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef nvg_helper_hpp
#define nvg_helper_hpp

#include "color.hpp"
#include <glm/mat3x3.hpp>

extern "C" struct NVGcontext;
extern "C" struct NVGcolor;

void nvgTransform(NVGcontext *, const glm::mat3 &);
NVGcolor nvgRGBA(Color);

#endif
