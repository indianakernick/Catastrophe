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
#include "framebuffer to png.hpp"
#include "../Libraries/tinyfiledialogs.h"
#include "register collision listeners.hpp"
#include <Simpleton/Time/get.hpp>

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
  
  renderingSystem.getCamera().windowSize.attachWindow(window.get());
  
  entityManager.init(inputSystem, physicsSystem, animationSystem, renderingSystem);
  
  const glm::vec2 WINDOW_METER_SIZE = static_cast<glm::vec2>(DEFAULT_WINDOW_PIXEL_SIZE) / DEFAULT_PIXELS_PER_METER;
  
  player = entityManager.create(makePlayer, b2Vec2(WINDOW_METER_SIZE.x / 2.0f, 10.0f));
  platform = entityManager.create(makePlatform,
    Rect({WINDOW_METER_SIZE.x / 2.0f, 1.0f}, {WINDOW_METER_SIZE.x, 1.0f})
  );
  
  renderingSystem.startMotionTrack(player);
  renderingSystem.startZoomTrack(player);
  
  screenshotMem = std::make_unique<uint8_t[]>(SCREENSHOT_MEM_SIZE);
  
  return true;
}

void AppImpl::quit() {
  renderingSystem.stopZoomTrack();
  renderingSystem.stopMotionTrack();

  entityManager.quit();
  renderingSystem.getCamera().windowSize.detachWindow();
  
  if constexpr (ENABLE_DEBUG_PHYSICS_RENDER) {
    physicsSystem.detachRenderer();
  }
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
    } else if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.scancode == SDL_SCANCODE_P) {
      takeScreenshot = true;
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
  if constexpr (ENABLE_GAME_RENDER) {
    renderingSystem.render(entityManager, renderingContext.getContext());
  }
  if constexpr (ENABLE_DEBUG_CAMERA_RENDER) {
    renderingSystem.cameraDebugRender(renderingContext.getContext());
  }
  
  if (takeScreenshot) {
    takeScreenshot = false;
    renderingContext.postRender(
      false,
      screenshotMem.get(),
      SCREENSHOT_MEM_SIZE
    );
    
    const char *filePath = tinyfd_saveFileDialog(
      "Save screenshot",
      "Screenshot.png",
      0,
      nullptr,
      "Image"
    );
    if (filePath != nullptr) {
      framebufferToPNG(
        filePath,
        renderingContext.getFramebufferSize(),
        screenshotMem.get()
      );
    }
  } else {
    renderingContext.postRender(ENABLE_FPS_RENDER);
  }
}
