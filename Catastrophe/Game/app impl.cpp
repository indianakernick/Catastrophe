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
#include "debug input.hpp"
#include "file constants.hpp"
#include "camera constants.hpp"
#include "register collision listeners.hpp"

std::unique_ptr<AppImpl> app = nullptr;

bool AppImpl::init() {
  windowLibrary.emplace(SDL_INIT_EVENTS);
  window = Platform::makeWindow(WINDOW_DESC);
  renderingContext.init(window.get());
  
  physicsSystem.init();
  if constexpr (ENABLE_DEBUG_PHYSICS_RENDER) {
    physicsSystem.attachRenderer(renderingContext.getContext());
  }
  registerCollisionListeners(physicsSystem.getContactListener());
  
  renderingSystem.getCamera().windowSize.addEventListener(inputSystem);
  
  entityManager.init(inputSystem, physicsSystem, animationSystem, renderingSystem);
  
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

  entityManager.quit();
  renderingSystem.getCamera().windowSize.remEventListener(inputSystem);
  
  physicsSystem.detachRenderer();
  physicsSystem.quit();
  
  renderingContext.quit();
  window.reset();
  windowLibrary = std::experimental::nullopt;
}

bool AppImpl::input(float) {
  SDL_Event e;
  unsigned eventCount = 0;
  while (eventCount != MAX_INPUT_EVENTS_PER_FRAME && SDL_PollEvent(&e)) {
    if constexpr (ENABLE_DEBUG_INPUT_LOG) {
      printEvent(e);
    }
    
    if (e.type == SDL_QUIT) {
      return false;
    } else {
      inputSystem.handleEvent(entityManager, e);
    }
    eventCount++;
  }
  return true;
}

bool AppImpl::update(const float delta) {
  physicsSystem.update(entityManager, delta);
  return true;
}

void AppImpl::render(const float delta) {
  animationSystem.update(entityManager, delta);
  renderingSystem.update(delta);
  
  renderingContext.preRender(renderingSystem.getCamera().toPixels());
  
  if constexpr (ENABLE_DEBUG_PHYSICS_RENDER) {
    physicsSystem.debugRender();
  }
  if constexpr (ENABLE_DEBUG_CAMERA_RENDER) {
    renderingSystem.cameraDebugRender(renderingContext.getContext());
  }
  if constexpr (ENABLE_GAME_RENDER) {
    renderingSystem.render(entityManager, renderingContext.getContext());
  }
  
  renderingContext.postRender(ENABLE_FPS_RENDER);
}
