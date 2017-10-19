//
//  render manager.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 16/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "render manager.hpp"

#include <cassert>
#include "layer names.hpp"

RenderManager::RenderManager()
  : layers(getNumLayers()) {
  for (auto &layer : layers) {
    //RenderingSystem and ParticleSystem both create a single job
    //for each layer but I'm reserving a few extra slots just in case
    layer.reserve(8);
  }
}

void RenderManager::init(RenderingContext &newRenderingContext) {
  assert(renderingContext == nullptr);
  renderingContext = &newRenderingContext;
}

void RenderManager::quit() {
  assert(renderingContext != nullptr);
  renderingContext = nullptr;
}

void RenderManager::addJob(const size_t layer, const std::shared_ptr<RenderJob> job) {
  if (!job->alive()) {
    return;
  }
  layers.at(layer).push_back(job);
}

void RenderManager::render() {
  for (auto &layer : layers) {
    for (auto j = layer.begin(); j != layer.end();) {
      if ((*j)->alive()) {
        (*j)->render(*renderingContext);
        ++j;
      } else {
        j = layer.erase(j);
      }
    }
  }
}

RenderingContext &RenderManager::getRenderingContext() const {
  assert(renderingContext);
  return *renderingContext;
}
