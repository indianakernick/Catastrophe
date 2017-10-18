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
#include <Simpleton/Utils/profiler.hpp>

void unPremultiplyAlpha(const glm::ivec2 imageSize, uint8_t *const data) {
  uint8_t *const end = data + imageSize.x * imageSize.y * 4;
  for (uint8_t *p = data; p != end; p += 4) {
    float r = p[0] / 255.0f;
    float g = p[1] / 255.0f;
    float b = p[2] / 255.0f;
    const float a = p[3] / 255.0f;
    r /= a;
    g /= a;
    b /= a;
    p[0] = r * 255.0f;
    p[1] = g * 255.0f;
    p[2] = b * 255.0f;
  }
}

void framebufferToPNG(
  const char *file,
  const glm::ivec2 imageSize,
  uint8_t *const data
) {
  PROFILE(Framebuffer to PNG);
  unPremultiplyAlpha(imageSize, data);
  const uint8_t *const lastRow = data + imageSize.x * (imageSize.y - 1) * 4;
  const int pitch = -imageSize.x * 4;
  if (stbi_write_png(file, imageSize.x, imageSize.y, 4, lastRow, pitch) == 0) {
    throw std::runtime_error("Failed to write image to file");
  }
}
