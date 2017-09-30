//
//  vector render.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 4/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef vector_render_hpp
#define vector_render_hpp

#include <glm/mat3x3.hpp>
#include "vector sprite.hpp"

Frame getFrame(const Sprite &, const std::string &, float);
void lerpFrames(float, Frame &, const Frame &);
void renderSprite(NVGcontext *, const Sprite &, const Frame &, glm::mat3);

#endif
