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

void RenderingSystem::init(RenderingManager &newRenderingMan, Camera &newCamera) {
  assert(!renderingMan);
  assert(!camera);
  renderingMan = &newRenderingMan;
  camera = &newCamera;
  const size_t numLayers = getNumLayers();
  layers.reserve(numLayers);
  for (size_t l = 0; l != numLayers; ++l) {
    layers.push_back(std::make_shared<Layer>(camera));
    renderingMan->addJob(l, layers.back());
  }
}

void RenderingSystem::quit() {
  assert(renderingMan);
  assert(camera);
  for (auto &layer : layers) {
    layer->kill();
  }
  layers.clear();
  camera = nullptr;
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

RenderingSystem::Layer::Layer(const Camera *camera)
  : camera(camera) {}

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
