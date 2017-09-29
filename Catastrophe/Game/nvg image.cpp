//
//  nvg image.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "nvg image.hpp"

#include <utility>
#include <nanovg/nanovg.h>

NVGimage::NVGimage(NVGcontext *ctx, const char *filename, const int imageFlags)
  : ctx(ctx),
    handle(nvgCreateImage(ctx, filename, imageFlags)) {}

NVGimage::NVGimage(NVGimage &&other)
  : ctx(std::exchange(other.ctx, nullptr)),
    handle(std::exchange(other.handle, 0)) {}

NVGimage::~NVGimage() {
  if (handle != 0) {
    nvgDeleteImage(ctx, handle);
  }
}

NVGimage &NVGimage::operator=(NVGimage &&other) {
  if (handle != 0) {
    nvgDeleteImage(ctx, handle);
  }
  ctx = std::exchange(other.ctx, nullptr);
  handle = std::exchange(other.handle, 0);
  return *this;
}

NVGimage::operator bool() const {
  return handle != 0;
}

bool NVGimage::operator!() const {
  return handle == 0;
}

int NVGimage::get() const {
  return handle;
}
