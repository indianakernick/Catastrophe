//
//  framebuffer to png.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 15/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef framebuffer_to_png_hpp
#define framebuffer_to_png_hpp

#include <glm/vec2.hpp>

void framebufferToPNG(const char *path, glm::ivec2, uint8_t *);

#endif
