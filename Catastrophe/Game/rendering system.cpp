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
#include "render manager.hpp"
#include "render component.hpp"
#include "rendering context.hpp"
#include <Simpleton/Utils/profiler.hpp>

void RenderingSystem::init(RenderManager &newRenderMan) {
  assert(!renderMan);
  renderMan = &newRenderMan;
  RenderingContext &context = renderMan->getRenderingContext();
  camera.windowSize.attachWindow(context.getWindow());
  const size_t numLayers = getNumLayers();
  layers.reserve(numLayers);
  for (size_t l = 0; l != numLayers; ++l) {
    layers.push_back(std::make_shared<Layer>(camera));
    renderMan->addJob(l, layers.back());
  }
}

void RenderingSystem::quit() {
  assert(renderMan);
  for (auto &layer : layers) {
    layer->dead = true;
  }
  layers.clear();
  camera.windowSize.detachWindow();
  renderMan = nullptr;
}

void RenderingSystem::add(
  const EntityID id,
  const CompPtr comp,
  const YAML::Node &node
) {
  assert(renderMan);
  const size_t layer = comp->getLayer();
  if (layer >= layers.size()) {
    throw std::range_error("Layer index out of range");
  }
  layers[layer]->comps.emplace(id, comp);
  comp->init(renderMan->getRenderingContext(), node);
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
  camera.debugRender(renderMan->getRenderingContext().getContext());
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

bool RenderingSystem::Layer::alive() const {
  return !dead;
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
