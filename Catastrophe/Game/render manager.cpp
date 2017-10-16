//
//  render manager.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 16/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "render manager.hpp"

#include "layer names.hpp"

RenderManager::RenderManager()
  : layers(getNumLayers()) {
  for (auto &layer : layers) {
    //RenderingSystem and ParticleSystem both create a single job
    //for each layer but I'm reserving a few extra slots just in case
    layer.reserve(8);
  }
}

void RenderManager::addJob(const size_t layer, const std::shared_ptr<RenderJob> job) {
  if (!job->alive()) {
    return;
  }
  layers[layer].push_back(job);
}

void RenderManager::render(RenderingContext &ctx) {
  for (auto &layer : layers) {
    for (auto j = layer.begin(); j != layer.end();) {
      if ((*j)->alive()) {
        (*j)->render(ctx);
        ++j;
      } else {
        j = layer.erase(j);
      }
    }
  }
}
