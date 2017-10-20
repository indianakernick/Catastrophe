//
//  simple tracking component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 20/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "simple tracking component.hpp"

#include "physics component.hpp"
#include "rendering component.hpp"

void SimpleTrackingComponent::init(const YAML::Node &) {
  motionTarget = makeMotionTarget();
  zoomTarget = makeZoomTarget();
}

void SimpleTrackingComponent::update(float) {
  AABB aabb(-0.5f, -0.5f, 0.5f, 0.5f);
  if (const auto renderingComp = getComp<RenderingComponent>()) {
    aabb = renderingComp->getAABB();
  } else if (const auto physicsComp = getComp<PhysicsComponent>()) {
    aabb = physicsComp->getAABB();
  }
  *motionTarget = static_cast<CameraMotionTarget>(aabb);
  *zoomTarget = motionTarget->halfSize * 2.0f;
}

CameraMotionTargetCPtr SimpleTrackingComponent::getMotionTarget() const {
  return motionTarget;
}

CameraZoomTargetCPtr SimpleTrackingComponent::getZoomTarget() const {
  return zoomTarget;
}
