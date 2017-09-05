//
//  nvg helper.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 4/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef nvg_helper_hpp
#define nvg_helper_hpp

#include <glm/mat3x3.hpp>

extern "C" struct NVGcontext;

void nvgTransform(NVGcontext *, const glm::mat3 &);

#endif
