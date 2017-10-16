//
//  app impl.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "app impl.hpp"

#include "debug input.hpp"
#include "player constants.hpp"
#include "systems registry.hpp"
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

  Systems::input = &inputSystem;
  Systems::spawn = &spawnSystem;
  Systems::physics = &physicsSystem;
  Systems::animation = &animationSystem;
  Systems::rendering = &renderingSystem;
  Systems::particle = &particleSystem;
  Systems::entities = &entityManager;
  Systems::renderer = &renderingContext;

  windowLibrary.emplace(SDL_INIT_EVENTS);
  window = Platform::makeWindow(WINDOW_DESC);
  renderingContext.init(window.get());
  renderManager.init(renderingContext);
  
  renderingSystem.init(renderManager);
  particleSystem.init();
  
  physicsSystem.init();
  if constexpr (ENABLE_DEBUG_PHYSICS_RENDER) {
    physicsSystem.attachRenderer(renderingContext.getContext());
  }
  registerCollisionListeners(physicsSystem.getContactListener());
  
  entityManager.init();
  spawnSystem.init(entityManager);
  
  entityManager.loadLevel("level 0.yaml");
  renderingSystem.startMotionTrack(PLAYER_ID);
  renderingSystem.startZoomTrack(PLAYER_ID);
  
  return true;
}

void AppImpl::quit() {
  PROFILE(Quit);

  renderingSystem.stopZoomTrack();
  renderingSystem.stopMotionTrack();
  
  spawnSystem.quit();
  entityManager.quit();
  
 if constexpr (ENABLE_DEBUG_PHYSICS_RENDER) {
    physicsSystem.detachRenderer();
  }
  physicsSystem.quit();
  
  particleSystem.quit();
  renderingSystem.quit();
  
  renderManager.quit();
  renderingContext.quit();
  window.reset();
  windowLibrary = std::experimental::nullopt;
  
  Systems::renderer = nullptr;
  Systems::entities = nullptr;
  Systems::particle = nullptr;
  Systems::rendering = nullptr;
  Systems::animation = nullptr;
  Systems::physics = nullptr;
  Systems::spawn = nullptr;
  Systems::input = nullptr;
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
    animationSystem.update(delta);
    renderingSystem.update(delta);
  }
  {
    PROFILE(Pre Render);
    renderingContext.preRender(renderingSystem.getCamera().transform.toPixels());
  }
  
  if constexpr (ENABLE_DEBUG_PHYSICS_RENDER) {
    PROFILE(Debug Physics Render);
    physicsSystem.debugRender();
  }
  if constexpr (ENABLE_GAME_RENDER) {
    PROFILE(Game Render);
    renderManager.render();
  }
  if constexpr (ENABLE_PARTICLE_RENDER) {
    PROFILE(Particle Render);
    particleSystem.render(renderingContext.getContext(), delta);
  }
  if constexpr (ENABLE_DEBUG_CAMERA_RENDER) {
    PROFILE(Debug Camera Render);
    renderingSystem.cameraDebugRender();
  }
  
  {
    PROFILE(Post Render);
    screenshot.postRender(renderingContext, ENABLE_FPS_RENDER);
  }
}
