//
//  app impl.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "app impl.hpp"

#include "player.hpp"
#include "platform.hpp"
#include "file constants.hpp"
#include "camera constants.hpp"
#include "register collision listeners.hpp"

std::unique_ptr<AppImpl> app = nullptr;

bool AppImpl::init() {
  SDLApp::initWindow(WINDOW_DESC, WINDOW_VSYNC);
  
  renderingSystem.init(renderer.get(), SPRITE_SHEET_PATH);
  if constexpr (ENABLE_DEBUG_CAMERA_RENDER) {
    renderingSystem.attachRendererToCamera();
  }
  
  physicsSystem.init();
  if constexpr (ENABLE_DEBUG_PHYSICS_RENDER) {
    physicsSystem.attachRenderer(renderingSystem.getRenderer());
  }
  registerCollisionListeners(physicsSystem.getContactListener());
  
  inputSystem.init();
  entityManager.init(inputSystem, physicsSystem, renderingSystem);
  
  const glm::vec2 WINDOW_METER_SIZE = static_cast<glm::vec2>(DEFAULT_WINDOW_PIXEL_SIZE) / DEFAULT_PIXELS_PER_METER;
  
  player = entityManager.create(makePlayer, b2Vec2(WINDOW_METER_SIZE.x / 2.0f, 10.0f));
  platform = entityManager.create(makePlatform,
    Rect({WINDOW_METER_SIZE.x / 2.0f, 1.0f}, {WINDOW_METER_SIZE.x, 2.0f})
  );
  
  renderingSystem.track(player);
  
  return true;
}

void AppImpl::quit() {
  renderingSystem.stopTracking();
  renderingSystem.detachRendererFromCamera();

  entityManager.quit();
  inputSystem.quit();
  
  physicsSystem.detachRenderer();
  physicsSystem.quit();
  
  renderingSystem.quit();
  
  SDLApp::quitWindow();
}

bool AppImpl::input(uint64_t) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      return false;
    } else {
      inputSystem.handleEvent(e);
    }
  }
  return true;
}

bool AppImpl::update(const uint64_t deltaMS) {
  const float delta = deltaMS / 1000.0f;
  physicsSystem.update(delta);
  entityManager.update(delta);
  renderingSystem.update(delta);
  return true;
}

void AppImpl::render(const uint64_t) {
  renderer.clear();
  if constexpr (ENABLE_DEBUG_PHYSICS_RENDER) {
    physicsSystem.debugRender();
  }
  if constexpr (ENABLE_DEBUG_CAMERA_RENDER) {
    renderingSystem.cameraDebugRender();
  }
  if constexpr (ENABLE_GAME_RENDER) {
    renderingSystem.render();
  }
  renderer.present();
}
