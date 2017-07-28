//
//  rendering context.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "rendering context.hpp"

#include "camera.hpp"
#include <SDL2/SDL_render.h>
#include "window constants.hpp"
#include <Simpleton/Platform/sdl error.hpp>
#include <Simpleton/Platform/system info.hpp>

RenderingContext::RenderingContext()
  : texture(nullptr, &SDL_DestroyTexture) {}

void RenderingContext::init(
  SDL_Renderer *newRenderer,
  const std::experimental::string_view sheetName
) {
  renderer = newRenderer;
  sheet = Unpack::makeSpritesheet(
    Platform::getResDir() + sheetName.data() + ".atlas",
    Platform::getResDir() + sheetName.data() + ".png"
  );
  const Unpack::Image &image = sheet.getImage();
  texture.reset(SDL_CreateTexture(
    renderer,
    SDL_PIXELFORMAT_ABGR8888,
    SDL_TEXTUREACCESS_STATIC,
    image.width(), image.height()
  ));
  CHECK_SDL_ERROR(SDL_UpdateTexture(
    texture.get(),
    nullptr,
    image.data(),
    static_cast<int>(image.pitch())
  ));
  CHECK_SDL_ERROR(SDL_SetTextureBlendMode(texture.get(), SDL_BLENDMODE_BLEND));
}

void RenderingContext::quit() {
  camera = nullptr;
  texture.reset();
  sheet = {};
  renderer = nullptr;
}

void RenderingContext::attachCamera(Camera &newCamera) {
  camera = &newCamera;
}

void RenderingContext::detachCamera() {
  camera = nullptr;
}

void RenderingContext::renderSprite(
  const std::experimental::string_view name,
  const int frame,
  const Rect dest
) {
  const std::string wholeName = name.to_string() + " " + std::to_string(frame);
  renderSprite(wholeName, dest);
}

namespace {
  SDL_Rect toSDL(const Unpack::RectPx rect) {
    return {rect.x, rect.y, rect.w, rect.h};
  }
  
  SDL_Rect toSDL(const RectPx rect) {
    return {rect.p.x, rect.p.y, rect.s.x, rect.s.y};
  }
}

void RenderingContext::renderSprite(
  const std::experimental::string_view name,
  const Rect dest
) {
  if (camera == nullptr) {
    return;
  }
  
  const RectPx destPixels = camera->transform(dest);
  
  if (!destPixels.interceptsWith(RectPx(WINDOW_PIXEL_SIZE))) {
    return;
  }
  
  const SDL_Rect src = toSDL(sheet.getSprite(name));
  const SDL_Rect dst = toSDL(destPixels);
  CHECK_SDL_ERROR(SDL_RenderCopy(
    renderer,
    texture.get(),
    &src,
    &dst
  ));
}

void RenderingContext::fillRect(const glm::tvec4<uint8_t> color, const Rect dest) {
  if (camera == nullptr) {
    return;
  }
  
  const RectPx destPixels = camera->transform(dest);
  
  if (!destPixels.interceptsWith(RectPx(WINDOW_PIXEL_SIZE))) {
    return;
  }
  
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  const SDL_Rect dst = toSDL(destPixels);
  SDL_RenderFillRect(renderer, &dst);
}
