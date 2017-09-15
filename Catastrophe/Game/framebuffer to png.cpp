//
//  framebuffer to png.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 15/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "framebuffer to png.hpp"

#include <memory>
#include <string>
#include <GL/glew.h>
#include <stdexcept>
#include <SDL2/SDL_opengl.h>
#include "stb_image_write.h"

void verticalFlip(uint8_t *pixels, const unsigned width, const unsigned height) {
  
}

void framebufferToPNG(const char *file, const unsigned w, const unsigned h) {
  framebufferToPNG(file, 0, 0, w, h);
}

void framebufferToPNG(const char *file, const int x, const int y, const unsigned w, const unsigned h) {
  auto pixels = std::make_unique<uint8_t[]>(4 * w * h);
  
  while (glGetError() != GL_NO_ERROR);
  glReadPixels(x, y, w, h, GL_RGBA, GL_UNSIGNED_BYTE, pixels.get());
  const GLenum error = glGetError();
  
  if (error != GL_NO_ERROR) {
    throw std::runtime_error(
      std::string("Failed to copy framebuffer into RAM: ") +
      reinterpret_cast<const char *>(gluErrorString(error))
    );
  }
  
  verticalFlip(pixels.get(), w, h);
  
  if (stbi_write_png(file, w, h, 4, pixels.get() + w * (h - 1) * 4, -w * 4) == 0) {
    throw std::runtime_error("Failed to write image to file");
  }
}
