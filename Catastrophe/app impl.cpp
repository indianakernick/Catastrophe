//
//  app impl.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "app impl.hpp"

#include "gun constants.hpp"
#include "file constants.hpp"
#include "window constants.hpp"
#include "handle player input.hpp"

std::unique_ptr<AppImpl> app = nullptr;

bool AppImpl::init() {
  SDLApp::initWindow(WINDOW_DESC, WINDOW_VSYNC);
  SDL_RenderSetLogicalSize(renderer.get(), WINDOW_PIXEL_SIZE.x, WINDOW_PIXEL_SIZE.y);
  renderingContext.init(renderer.get(), SPRITE_SHEET_PATH);
  renderingContext.attachCamera(camera);
  player = entities.make<Player>(MINI_GUN);
  camera.setTarget(*entities.get(player));
  return true;
}

void AppImpl::quit() {
  camera.unsetTarget(*entities.get(player));
  renderingContext.detachCamera();
  renderingContext.quit();
  SDLApp::quitWindow();
}

bool AppImpl::input(uint64_t) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      return false;
    } else {
      handlePlayerInput(*entities.get<Player>(player), e);
    }
  }
  return true;
}

bool AppImpl::update(const uint64_t deltaMS) {
  entities.update(deltaMS / 1000.0f);
  return true;
}

void AppImpl::render(const uint64_t deltaMS) {
  renderer.clear();
  
  renderingContext.fillRect({255, 0, 0, 255}, {0, 0, 1, 1});
  
  entities.render(renderingContext);
  camera.update(deltaMS / 1000.0f);
  renderer.present();
}
