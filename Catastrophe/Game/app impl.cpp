//
//  app impl.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "app impl.hpp"

#include "level file.hpp"
#include "debug input.hpp"
#include "file constants.hpp"
#include "camera constants.hpp"
#include "framebuffer to png.hpp"
#include <Simpleton/Utils/profiler.hpp>
#include "../Libraries/tinyfiledialogs.h"
#include "register collision listeners.hpp"
#include <Simpleton/Platform/system info.hpp>

std::unique_ptr<AppImpl> app = nullptr;

bool AppImpl::init() {
  PROFILE(Init);

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
  
  player = loadLevel(Platform::getResDir() + "level 0.yaml", entityManager);
  
  renderingSystem.startMotionTrack(player);
  renderingSystem.startZoomTrack(player);
  
  screenshotMem = std::make_unique<uint8_t[]>(SCREENSHOT_MEM_SIZE);
  
  return true;
}

void AppImpl::quit() {
  PROFILE(Quit);

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
  PROFILE(Input);

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
      inputSystem.handleEvent(e);
    }
    eventCount++;
  }
  return true;
}

bool AppImpl::update(const float delta) {
  PROFILE(Update);
  physicsSystem.update(delta);
  return true;
}

void AppImpl::render(const float delta) {
  PROFILE(Render);
  
  {
    PROFILE(Anim);
    animationSystem.update(delta);
    renderingSystem.update(delta);
  }
  {
    PROFILE(Pre Render);
    renderingContext.preRender(renderingSystem.getCamera().toPixels());
  }
  
  if constexpr (ENABLE_DEBUG_PHYSICS_RENDER) {
    physicsSystem.debugRender();
  }
  if constexpr (ENABLE_GAME_RENDER) {
    PROFILE(Game Render);
    renderingSystem.render(renderingContext.getContext());
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
    PROFILE(Post Render);
    renderingContext.postRender(ENABLE_FPS_RENDER);
  }
}
