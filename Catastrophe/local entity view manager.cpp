//
//  local entity view manager.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "local entity view manager.hpp"

LocalEntityViewManager::LocalEntityViewManager(
  SDL_Renderer *renderer,
  const std::string &spritesheetPath
) : camera(),
    renderingContext(renderer, spritesheetPath, camera) {}

void LocalEntityViewManager::render(const uint64_t delta) {
  for (auto v = views.cbegin(); v != views.cend(); ++v) {
    v->second->render(renderingContext, delta);
  }
}

void LocalEntityViewManager::addView(
  const EntityID id,
  const std::shared_ptr<LocalEntityView> view
) {
  views.emplace(id, view);
}

void LocalEntityViewManager::remView(const EntityID id) {
  views.erase(id);
}

Camera &LocalEntityViewManager::getCamera() {
  return camera;
}
