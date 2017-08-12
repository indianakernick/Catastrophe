//
//  rendering system.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "rendering system.hpp"

#include "camera.hpp"
#include "camera constants.hpp"

void RenderingSystem::init(SDL_Renderer *sdlRenderer, const std::experimental::string_view sheet) {
  renderer.init(sdlRenderer, sheet, &camera);
  camera.zoomTo(MAX_ZOOM);
}

void RenderingSystem::quit() {
  renderer.quit();
}

void RenderingSystem::add(const EntityID id, const std::shared_ptr<RenderComponent> comp) {
  components.emplace(id, comp);
}

void RenderingSystem::rem(const EntityID id) {
  components.erase(id);
}

void RenderingSystem::update(const float delta) {
  camera.update(delta);
}

void RenderingSystem::render() {
  for (auto c = components.cbegin(); c != components.cend(); ++c) {
    c->second->render(renderer);
  }
}

void RenderingSystem::track(const EntityID entity) {
  auto iter = components.find(entity);
  assert(iter != components.end());
  const CameraTarget *target = iter->second->getCameraTarget();
  assert(target);
  camera.trackTarget(target);
}

void RenderingSystem::stopTracking() {
  camera.stopTracking();
}

RenderingContext &RenderingSystem::getRenderer() {
  return renderer;
}

Camera &RenderingSystem::getCamera() {
  return camera;
}
