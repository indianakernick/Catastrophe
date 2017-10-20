//
//  app impl.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "app impl.hpp"

#include "systems.hpp"
#include "debug input.hpp"
#include "global flags.hpp"
#include "player constants.hpp"
#include <Simpleton/Utils/profiler.hpp>
#include "register collision listeners.hpp"

std::unique_ptr<AppImpl> app = nullptr;

/*

Mines
Switches
Missle launchers
  Missles
Air Drones
Ground Drones
Droppers
Coins

Pink pentagon was stolen from a museum
Main character hired to steal the pink pentagon back

*/

bool AppImpl::init() {
  PROFILE(Init);

  #define COMPONENT(N, ID_NAME) Systems::ID_NAME = &ID_NAME##System;
  #define LAST_COMPONENT(N, ID_NAME) COMPONENT(N, ID_NAME)
  COMPONENTS
  #undef LAST_COMPONENT
  #undef COMPONENT

  windowLibrary.emplace(SDL_INIT_EVENTS);
  window = Platform::makeWindow(WINDOW_DESC);
  renderingContext.init(window.get());
  renderingManager.init(renderingContext);
  
  renderingSystem.init(renderingManager, camera);
  particleSystem.init(renderingManager);
  trackingSystem.init(camera);
  
  physicsSystem.init(renderingManager);
  registerCollisionListeners(physicsSystem.getContactListener());
  
  entityManager.init();
  spawnSystem.init(entityManager);
  
  entityManager.loadLevel("level 0.yaml");
  trackingSystem.startTracking(PLAYER_ID);
  
  return true;
}

void AppImpl::quit() {
  PROFILE(Quit);

  trackingSystem.stopTracking();
  
  spawnSystem.quit();
  entityManager.quit();
  
  physicsSystem.quit();
  
  trackingSystem.quit();
  
  particleSystem.quit();
  renderingSystem.quit();
  
  renderingManager.quit();
  renderingContext.quit();
  window.reset();
  windowLibrary = std::experimental::nullopt;
  
  #define COMPONENT(N, ID_NAME) Systems::ID_NAME = nullptr;
  #define LAST_COMPONENT(N, ID_NAME) COMPONENT(N, ID_NAME)
  COMPONENTS
  #undef LAST_COMPONENT
  #undef COMPONENT
}

bool AppImpl::input(float) {
  PROFILE(Input);

  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    PROFILE(Input event loop);
    if constexpr (ENABLE_DEBUG_INPUT_LOG) {
      printEvent(e);
    }
    
    if (e.type == SDL_QUIT) {
      return false;
    } else if (!screenshot.handleEvent(e)){
      inputSystem.handleEvent(e);
    }
  }
  return true;
}

bool AppImpl::update(const float delta) {
  PROFILE(Update);
  
  spawnSystem.update(delta);
  physicsSystem.update(delta);
  return true;
}

void AppImpl::render(const float delta) {
  PROFILE(Render);
  
  {
    PROFILE(Anim);
    camera.update(window.size(), delta);
    animationSystem.update(delta);
    trackingSystem.update(delta);
    particleSystem.update(delta);
  }
  {
    PROFILE(Pre Render);
    renderingContext.preRender(camera.transform.toPixels());
  }
  
  renderingManager.render();
  
  {
    PROFILE(Post Render);
    screenshot.postRender(renderingContext, ENABLE_FPS_RENDER);
  }
}
