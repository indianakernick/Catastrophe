//
//  tracking system.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "tracking system.hpp"

#include "camera.hpp"
#include "tracking component.hpp"

void TrackingSystem::init(Camera &newCamera) {
  assert(!camera);
  camera = &newCamera;
}

void TrackingSystem::quit() {
  assert(camera);
  camera = nullptr;
}

void TrackingSystem::add(
  const EntityID id,
  const CompPtr comp,
  const YAML::Node &node
) {
  comp->init(node);
  comps.emplace(id, comp);
}

void TrackingSystem::rem(const EntityID id) {
  comps.erase(id);
}

void TrackingSystem::update(const float delta) {
  for (auto &pair : comps) {
    pair.second->update(delta);
  }
}

void TrackingSystem::startTracking(const EntityID id) {
  const auto iter = comps.find(id);
  if (iter == comps.end()) {
    throw std::runtime_error("Cannot track entity that doesn't exist");
  }
  const CompPtr comp = iter->second;
  camera->motionTrack.start(comp->getMotionTarget());
  camera->zoomTrack.start(comp->getZoomTarget());
}

void TrackingSystem::stopTracking() {
  camera->motionTrack.stop();
  camera->zoomTrack.stop();
}
