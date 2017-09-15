//
//  framebuffer to png.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 15/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef framebuffer_to_png_hpp
#define framebuffer_to_png_hpp

void framebufferToPNG(const char *path, unsigned w, unsigned h);
void framebufferToPNG(const char *path, int x, int y, unsigned w, unsigned h);

#endif
