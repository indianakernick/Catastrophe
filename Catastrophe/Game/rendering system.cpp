//
//  rendering system.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "rendering system.hpp"

#include "camera.hpp"
#include "nanovg.hpp"
#include "layer names.hpp"
#include "global flags.hpp"
#include "entity manager.hpp"
#include "rendering context.hpp"
#include "rendering manager.hpp"
#include "rendering component.hpp"
#include <Simpleton/Utils/profiler.hpp>

void RenderingSystem::init(RenderingManager &newRenderingMan) {
  assert(!renderingMan);
  renderingMan = &newRenderingMan;
  RenderingContext &context = renderingMan->getRenderingContext();
  camera.windowSize.attachWindow(context.getWindow());
  const size_t numLayers = getNumLayers();
  layers.reserve(numLayers);
  for (size_t l = 0; l != numLayers; ++l) {
    layers.push_back(std::make_shared<Layer>(camera));
    renderingMan->addJob(l, layers.back());
  }
}

void RenderingSystem::quit() {
  assert(renderingMan);
  for (auto &layer : layers) {
    layer->kill();
  }
  layers.clear();
  camera.windowSize.detachWindow();
  renderingMan = nullptr;
}

void RenderingSystem::add(
  const EntityID id,
  const CompPtr comp,
  const YAML::Node &node
) {
  assert(renderingMan);
  comp->init(renderingMan->getRenderingContext(), node);
  const size_t layer = comp->getLayer();
  if (layer >= layers.size()) {
    throw std::range_error("Layer index out of range");
  }
  layers[layer]->comps.emplace(id, comp);
}

void RenderingSystem::rem(const EntityID id) {
  for (auto &layer : layers) {
    layer->comps.erase(id);
  }
}

void RenderingSystem::update(const float delta) {
  camera.update(delta);
}

void RenderingSystem::cameraDebugRender() {
  camera.debugRender(renderingMan->getRenderingContext().getContext());
}

void RenderingSystem::startMotionTrack(const EntityID id) {
  const CompPtr comp = findComp(id);
  if (comp == nullptr) {
    throw std::runtime_error("Cannot track entity that doesn't exist");
  }
  camera.motionTrack.start(comp->getMotionTarget());
}

void RenderingSystem::stopMotionTrack() {
  camera.motionTrack.stop();
}

void RenderingSystem::startZoomTrack(const EntityID id) {
  const CompPtr comp = findComp(id);
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

RenderingSystem::Layer::Layer(const Camera &camera)
  : camera(&camera) {}

void RenderingSystem::Layer::render(RenderingContext &renderingContext) {
  if constexpr (ENABLE_GAME_RENDER) {
    PROFILE(RenderingSystem::Layer::render);
  
    assert(camera);
    NVGcontext *const ctx = renderingContext.getContext();
    for (auto &pair : comps) {
      pair.second->preRender();
      if (camera->transform.visibleMeters(pair.second->getAABB())) {
        nvgSave(ctx);
        pair.second->render(ctx);
        nvgRestore(ctx);
      }
    }
  }
}

RenderingSystem::CompPtr RenderingSystem::findComp(const EntityID id) {
  for (auto &layer : layers) {
    auto iter = layer->comps.find(id);
    if (iter != layer->comps.end()) {
      return iter->second;
    }
  }
  return nullptr;
}
