//
//  app impl.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "app impl.hpp"

#include "constants.hpp"

std::unique_ptr<AppImpl> app = nullptr;

AppImpl::AppImpl() {}

bool AppImpl::init() {
  SDLApp::initWindow(WINDOW_DESC, true);
  SDL_RenderSetLogicalSize(renderer.get(), WINDOW_PIXEL_SIZE.x, WINDOW_PIXEL_SIZE.y);
  return true;
}

void AppImpl::quit() {
  SDLApp::quitWindow();
}

bool AppImpl::input(uint64_t) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      return false;
    } else if (e.type == SDL_KEYDOWN) {
      if (e.key.repeat == 0) {
        switch (e.key.keysym.scancode) {
          case SDL_SCANCODE_W:
            player.startMoving(Math::Dir::UP);
            break;
          case SDL_SCANCODE_D:
            player.startMoving(Math::Dir::RIGHT);
            break;
          case SDL_SCANCODE_S:
            player.startMoving(Math::Dir::DOWN);
            break;
          case SDL_SCANCODE_A:
            player.startMoving(Math::Dir::LEFT);
          default: ;
        }
      }
    } else if (e.type == SDL_KEYUP) {
      switch (e.key.keysym.scancode) {
        case SDL_SCANCODE_W:
          player.stopMoving(Math::Dir::UP);
          break;
        case SDL_SCANCODE_D:
          player.stopMoving(Math::Dir::RIGHT);
          break;
        case SDL_SCANCODE_S:
          player.stopMoving(Math::Dir::DOWN);
          break;
        case SDL_SCANCODE_A:
          player.stopMoving(Math::Dir::LEFT);
        default: ;
      }
    }
  }
  return true;
}

bool AppImpl::update(const uint64_t deltaMS) {
  player.update(deltaMS / 1000.0f);
  return true;
}

void AppImpl::render(const uint64_t) {
  renderer.clear();
  player.render(renderer.get());
  renderer.present();
}
