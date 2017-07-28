//
//  rendering context.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "rendering context.hpp"

#include <SDL2/SDL_render.h>
#include "window constants.hpp"
#include <Simpleton/Platform/sdl error.hpp>
#include <Simpleton/Platform/system info.hpp>

Renderer::Renderer()
  : texture(nullptr, &SDL_DestroyTexture) {}

void Renderer::init(
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

void Renderer::quit() {
  texture.reset();
  sheet = {};
  renderer = nullptr;
}

std::shared_ptr<VisibleComponent> Renderer::create(
  const EntityID entityID,
  const std::string &sprite
) {
  auto comp = std::make_shared<VisibleComponent>();
  comp->spriteName = sprite;
  components.emplace(entityID, comp);
  return comp;
}

void Renderer::destroy(const EntityID entityID) {
  auto iter = components.find(entityID);
  if (iter != components.cend()) {
    components.erase(iter);
  }
}

void Renderer::render() {
  for (auto c = components.cbegin(); c != components.cend(); ++c) {
    const VisibleComponent &comp = *c->second;
    renderSprite(comp.spriteName, comp.rect);
  }
}

void Renderer::renderSprite(
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
  
  RectPx transform(const Rect rect) {
    return {
      rect.p * -PIXELS_PER_METER,
      rect.s * PIXELS_PER_METER
    };
  }
}

void Renderer::renderSprite(
  const std::experimental::string_view name,
  const Rect dest
) {
  const RectPx destPixels = transform(dest);
  
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
