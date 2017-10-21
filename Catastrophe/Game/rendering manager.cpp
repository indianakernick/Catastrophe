//
//  rendering manager.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 16/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "rendering manager.hpp"

#include <cassert>
#include "layer names.hpp"
#include <Simpleton/Utils/profiler.hpp>

RenderingManager::RenderingManager()
  : layers(getNumLayers()) {
  for (auto &layer : layers) {
    //RenderingSystem and ParticleSystem both create a single job
    //for each layer but I'm reserving a few extra slots just in case
    layer.reserve(8);
  }
}

void RenderingManager::init(RenderingContext &newRenderingContext) {
  assert(renderingContext == nullptr);
  renderingContext = &newRenderingContext;
}

void RenderingManager::quit() {
  assert(renderingContext != nullptr);
  renderingContext = nullptr;
}

void RenderingManager::addJob(const size_t layer, const std::shared_ptr<RenderingJob> job) {
  if (!job->alive()) {
    return;
  }
  layers.at(layer).push_back(job);
}

void RenderingManager::render() {
  PROFILE(RenderingManager render);
  
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

RenderingContext &RenderingManager::getRenderingContext() const {
  assert(renderingContext);
  return *renderingContext;
}
