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
  PROFILE(AppImpl init);

  windowLibrary.emplace(SDL_INIT_EVENTS);
  window = Platform::makeWindow(WINDOW_DESC);
  renderingContext.init(window.get());
  renderingManager.init(renderingContext);
  
  cameraDebugRenderer.init(camera, renderingManager);
  
  Systems::rendering.init(renderingManager, camera);
  Systems::particle.init(renderingManager);
  Systems::tracking.init(camera);
  
  Systems::physics.init(renderingManager);
  registerCollisionListeners(Systems::physics.getContactListener());
  
  entityManager.init();
  Systems::spawn.init(entityManager);
  
  entityManager.loadLevel("level 0.yaml");
  Systems::tracking.startTracking(PLAYER_ID);
  
  return true;
}

void AppImpl::quit() {
  PROFILE(AppImpl quit);

  Systems::tracking.stopTracking();
  
  Systems::spawn.quit();
  entityManager.quit();
  
  Systems::physics.quit();
  
  Systems::tracking.quit();
  Systems::particle.quit();
  Systems::rendering.quit();
  
  cameraDebugRenderer.quit();
  
  renderingManager.quit();
  renderingContext.quit();
  window.reset();
  windowLibrary = std::experimental::nullopt;
}

bool AppImpl::input(float) {
  PROFILE(AppImpl input);

  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    PROFILE(Event loop);
    if constexpr (ENABLE_DEBUG_INPUT_LOG) {
      printEvent(e);
    }
    
    if (e.type == SDL_QUIT) {
      return false;
    } else if (!screenshot.handleEvent(e)) {
      Systems::input.handleEvent(e, camera.transform.toMeters());
    }
  }
  return true;
}

bool AppImpl::update(const float delta) {
  PROFILE(AppImpl update);
  
  Systems::ai.update(delta);
  Systems::spawn.update(delta);
  Systems::physics.update(delta);
  return true;
}

void AppImpl::render(const float delta) {
  PROFILE(AppImpl render);
  
  {
    PROFILE(Anim);
    camera.update(window.size(), delta);
    Systems::animation.update(delta);
    Systems::tracking.update(delta);
    Systems::particle.update(delta);
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
