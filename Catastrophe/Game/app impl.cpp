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

#include <Simpleton/Platform/system info.hpp>
#include "vector file.hpp"
#include "vector render.hpp"

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
  renderingSystem.getCamera().windowSize.addEventListener(inputSystem);
  
  entityManager.init(inputSystem, physicsSystem, renderingSystem);
  
  const glm::vec2 WINDOW_METER_SIZE = static_cast<glm::vec2>(DEFAULT_WINDOW_PIXEL_SIZE) / DEFAULT_PIXELS_PER_METER;
  
  player = entityManager.create(makePlayer, b2Vec2(WINDOW_METER_SIZE.x / 2.0f, 10.0f));
  platform = entityManager.create(makePlatform,
    Rect({WINDOW_METER_SIZE.x / 2.0f, 1.0f}, {WINDOW_METER_SIZE.x, 2.0f})
  );
  
  renderingSystem.track(player);
  
  fpsCounter.init();
  
  sprite = loadSprite((Platform::getResDir() + "player sprite.yaml").c_str());
  
  return true;
}

void AppImpl::quit() {
  renderingSystem.stopTracking();
  renderingSystem.detachRendererFromCamera();

  entityManager.quit();
  renderingSystem.getCamera().windowSize.remEventListener(inputSystem);
  inputSystem.quit();
  
  physicsSystem.detachRenderer();
  physicsSystem.quit();
  
  renderingSystem.quit();
  
  SDLApp::quitWindow();
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
      inputSystem.handleEvent(e);
    }
    eventCount++;
  }
  return true;
}

bool AppImpl::update(const float delta) {
  physicsSystem.update(delta);
  entityManager.update(delta);
  renderingSystem.update(delta);
  return true;
}

void AppImpl::render(const float delta) {
  renderer.clear();
  if constexpr (ENABLE_DEBUG_PHYSICS_RENDER) {
    //physicsSystem.debugRender();
  }
  if constexpr (ENABLE_DEBUG_CAMERA_RENDER) {
    //renderingSystem.cameraDebugRender();
  }
  if constexpr (ENABLE_GAME_RENDER) {
    //renderingSystem.render();
  }
  
  progress += delta;
  while (progress > sprite.animations.at("Run").durationSec) {
    progress -= sprite.animations.at("Run").durationSec;
  }
  renderSprite(renderingSystem.getRenderer(), sprite, "Run", {}, progress, true);
  
  if constexpr (ENABLE_FPS_RENDER) {
    fpsCounter.frame();
    //fpsCounter.get() returns uint32_t
    const unsigned frames = fpsCounter.get();
    
    char stringBuf[32];
    //@TODO use std::to_chars
    const int err = std::snprintf(stringBuf, sizeof(stringBuf), "FPS: %u", frames);
    assert(0 < err && err < static_cast<int>(sizeof(stringBuf)));
  
    renderingSystem.getRenderer().renderDebugText(
      {255, 255, 255, 255},
      {0, 0},
      stringBuf
    );
  }
  
  renderer.present();
}
