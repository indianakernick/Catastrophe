//
//  game view.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "game view.hpp"

#include "constants.hpp"

void GameView::init(SDL_Renderer *newRenderer, const std::string &sheetPath) {
  renderer = newRenderer;
  sprites.reserve(100);
  sheet = Unpack::makeSpritesheet(sheetPath + ".atlas", sheetPath + ".png");
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

void GameView::quit() {
  renderer = nullptr;
}

namespace {
  SDL_Rect makeRect(const Unpack::RectPx rect) {
    return {rect.x, rect.y, rect.w, rect.h};
  }
}

void GameView::render(uint64_t) {
  for (auto s = sprites.cbegin(); s != sprites.cend(); ++s) {
    const SDL_Rect src = makeRect(sheet.getSprite(s->second.name));
    const SDL_Rect dst = camera.transform(s->second.pos, s->second.size);
    SDL_RenderCopy(renderer, texture.get(), &src, &dst);
  }
}

void GameView::createSprite(
  const ActorID id,
  const std::string &name,
  const glm::vec2 pos,
  const glm::vec2 size
) {
  sprites.insert({id, {name, pos, size}});
}

void GameView::destroySprite(const ActorID id) {
  sprites.erase(id);
}

void GameView::moveSprite(const ActorID id, const glm::vec2 newPos) {
  sprites.at(id).pos = newPos;
}
