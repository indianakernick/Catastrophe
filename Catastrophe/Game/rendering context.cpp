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
  texture.reset();
  sheet = {};
  renderer = nullptr;
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
  const auto [dst, ok] = rectToPixels(dest);
  if (!ok) return;
  
  const SDL_Rect src = toSDL(sheet.getSprite(name));
  CHECK_SDL_ERROR(SDL_RenderCopy(
    renderer,
    texture.get(),
    &src,
    &dst
  ));
}

void RenderingContext::renderRect(const Color color, const Rect dest) {
  const auto [dst, ok] = rectToPixels(dest);
  if (!ok) return;
  
  CHECK_SDL_ERROR(
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a)
  );
  CHECK_SDL_ERROR(SDL_RenderFillRect(renderer, &dst));
}

void RenderingContext::attachCamera(const Camera *newCamera) {
  camera = newCamera;
}

void RenderingContext::detachCamera() {
  camera = nullptr;
}

std::pair<SDL_Rect, bool> RenderingContext::rectToPixels(const Rect rect) {
  if (camera == nullptr) {
    return {{}, false};
  }
  const RectPx destPixels = {
    camera->posToPixels(rect.p),
    camera->sizeToPixels(rect.s)
  };
  if (!destPixels.interceptsWith(RectPx(WINDOW_PIXEL_SIZE))) {
    return {{}, false};
  } else {
    return {toSDL(destPixels), true};
  }
}
