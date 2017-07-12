//
//  rendering context.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "rendering context.hpp"

#include "constants.hpp"

RenderingContext::RenderingContext(
  SDL_Renderer *renderer,
  const std::string &spriteSheetPath,
  Camera &camera
) : renderer(renderer),
    sheet(Unpack::makeSpritesheet(
      spriteSheetPath + ".atlas",
      spriteSheetPath + ".png"
    )),
    texture(nullptr, &SDL_DestroyTexture),
    camera(camera) {
  const Unpack::Image &image = sheet.getImage();
  texture.reset(SDL_CreateTexture(
    renderer,
    SDL_PIXELFORMAT_ABGR8888,
    SDL_TEXTUREACCESS_STATIC,
    image.width(),
    image.height()
  ));
  SDL_UpdateTexture(texture.get(), nullptr, image.data(), static_cast<int>(image.pitch()));
  SDL_SetTextureBlendMode(texture.get(), SDL_BLENDMODE_BLEND);
  
  SDL_RenderSetLogicalSize(renderer, WINDOW_PIXEL_SIZE.x, WINDOW_PIXEL_SIZE.y);
}

namespace {
  SDL_Rect castRect(const Unpack::RectPx rect) {
    return {rect.x, rect.y, rect.w, rect.h};
  }
  
  SDL_Rect castRect(const RectPx rect) {
    return {rect.p.x, rect.p.y, rect.s.x, rect.s.y};
  }
}

void RenderingContext::renderSprite(const std::string &name, const Rect rect) {
  const SDL_Rect src = castRect(sheet.getSprite(name));
  const SDL_Rect dst = castRect(camera.transform(rect));
  SDL_RenderCopy(renderer, texture.get(), &src, &dst);
}

void RenderingContext::renderSprite(
  const std::string &name,
  const Rect rect,
  const double angle
) {
  const SDL_Rect src = castRect(sheet.getSprite(name));
  const SDL_Rect dst = castRect(camera.transform(rect));
  SDL_RenderCopyEx(renderer, texture.get(), &src, &dst, angle, nullptr, SDL_FLIP_NONE);
}

namespace {
  SDL_RendererFlip castFlip(const Flip flip) {
    switch (flip) {
      case Flip::NONE:
        return SDL_FLIP_NONE;
      case Flip::HORI:
        return SDL_FLIP_HORIZONTAL;
      case Flip::VERT:
        return SDL_FLIP_VERTICAL;
      case Flip::BOTH:
        using Underlying = std::underlying_type_t<SDL_RendererFlip>;
        return static_cast<SDL_RendererFlip>(
          static_cast<Underlying>(SDL_FLIP_HORIZONTAL) |
          static_cast<Underlying>(SDL_FLIP_VERTICAL)
        );
    }
  }
}

void RenderingContext::renderSprite(
  const std::string &name,
  const Rect rect,
  const double angle,
  const glm::ivec2 centerPoint,
  const Flip flip
) {
  const SDL_Rect src = castRect(sheet.getSprite(name));
  const SDL_Rect dst = castRect(camera.transform(rect));
  const SDL_Point center = {centerPoint.x, centerPoint.y};
  SDL_RenderCopyEx(renderer, texture.get(), &src, &dst, angle, &center, castFlip(flip));
}
