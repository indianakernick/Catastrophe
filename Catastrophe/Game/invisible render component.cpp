//
//  invisible render component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 4/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "invisible render component.hpp"

InvisibleRenderComponent::InvisibleRenderComponent(const YAML::Node &, const YAML::Node &) {}

void InvisibleRenderComponent::preRender() {}

void InvisibleRenderComponent::render(NVGcontext *) {}

CameraMotionTargetCPtr InvisibleRenderComponent::getMotionTarget() const {
  return nullptr;
}

CameraZoomTargetCPtr InvisibleRenderComponent::getZoomTarget() const {
  return nullptr;
}

Rect InvisibleRenderComponent::getAABB() const {
  Rect rect;
  rect.p = {INFINITY, INFINITY};
  rect.s = {0.0f, 0.0f};
  return rect;
}
