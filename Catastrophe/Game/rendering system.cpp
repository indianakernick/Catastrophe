//
//  rendering system.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "rendering system.hpp"

void RenderingSystem::init(SDL_Renderer *renderer, const std::experimental::string_view sheet) {
  context.init(renderer, sheet);
}

void RenderingSystem::quit() {
  context.quit();
}

void RenderingSystem::add(const EntityID id, const std::shared_ptr<RenderComponent> comp) {
  components.emplace(id, comp);
}

void RenderingSystem::rem(const EntityID id) {
  components.erase(id);
}

void RenderingSystem::render() {
  for (auto c = components.cbegin(); c != components.cend(); ++c) {
    c->second->render(context);
  }
}

void RenderingSystem::attachCamera(const Camera *camera) {
  context.attachCamera(camera);
}

void RenderingSystem::detachCamera() {
  context.detachCamera();
}
