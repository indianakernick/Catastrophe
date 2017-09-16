//
//  framebuffer to png.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 15/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "framebuffer to png.hpp"

#include <stdexcept>
#include "stb_image_write.h"

void framebufferToPNG(
  const char *file,
  const glm::ivec2 imageSize,
  const uint8_t *const data
) {
  const uint8_t *const lastRow = data + imageSize.x * (imageSize.y - 1) * 4;
  const int pitch = -imageSize.x * 4;
  if (stbi_write_png(file, imageSize.x, imageSize.y, 4, lastRow, pitch) == 0) {
    throw std::runtime_error("Failed to write image to file");
  }
}
