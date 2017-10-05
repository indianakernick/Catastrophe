//
//  rendering system.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "rendering system.hpp"

#include "camera.hpp"
#include "entity manager.hpp"
#include "render component.hpp"

void RenderingSystem::add(const EntityID id, const std::shared_ptr<RenderComponent> comp) {
  const size_t layer = comp->getLayer();
  while (layers.size() <= layer) {
    layers.emplace_back();
  }
  layers[layer].emplace(id, comp);
}

void RenderingSystem::rem(const EntityID id) {
  for (auto &layer : layers) {
    layer.erase(id);
  }
}

void RenderingSystem::update(const float delta) {
  camera.update(delta);
}

void RenderingSystem::render(NVGcontext *const context) {
  for (auto &layer : layers) {
    for (auto &pair : layer) {
      pair.second->preRender();
      if (camera.visibleMeters(pair.second->getAABB())) {
        pair.second->render(context);
      }
    }
  }
}

void RenderingSystem::cameraDebugRender(NVGcontext *context) {
  camera.debugRender(context);
}

void RenderingSystem::startMotionTrack(const EntityID id) {
  CompPtr comp = findComp(id);
  if (comp == nullptr) {
    throw std::runtime_error("Cannot track entity that doesn't exist");
  }
  camera.motionTrack.start(comp->getMotionTarget());
}

void RenderingSystem::stopMotionTrack() {
  camera.motionTrack.stop();
}

void RenderingSystem::startZoomTrack(const EntityID id) {
  CompPtr comp = findComp(id);
  if (comp == nullptr) {
    throw std::runtime_error("Cannot track entity that doesn't exist");
  }
  camera.zoomTrack.start(comp->getZoomTarget());
}

void RenderingSystem::stopZoomTrack() {
  camera.zoomTrack.stop();
}

Camera &RenderingSystem::getCamera() {
  return camera;
}

RenderingSystem::CompPtr RenderingSystem::findComp(const EntityID id) {
  for (auto &layer : layers) {
    auto iter = layer.find(id);
    if (iter != layer.end()) {
      return iter->second;
    }
  }
  return nullptr;
}
