//
//  basic render component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 3/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "basic render component.hpp"

#include "entity.hpp"
#include "nvg helper.hpp"
#include "yaml helper.hpp"
#include "layer names.hpp"
#include "animation component.hpp"

void BasicRenderComponent::init(RenderingContext &, const YAML::Node &node) {
  glm::vec2 scale = {1.0f, 1.0f};
  getOptional(scale, node, "scale");
  layer = 0;
  if (const YAML::Node &layerNode = node["layer"]) {
    layer = getLayerIndex(layerNode.Scalar());
  }
  rect = makeMotionTarget(glm::vec2(), scale);
  size = makeZoomTarget(scale);
}

void BasicRenderComponent::preRender() {
  rect->c = getEntity().get<AnimationComponent>()->getModelMat()[2];
}

CameraMotionTargetCPtr BasicRenderComponent::getMotionTarget() const {
  return rect;
}

CameraZoomTargetCPtr BasicRenderComponent::getZoomTarget() const {
  return size;
}

Rect BasicRenderComponent::getAABB() const {
  return static_cast<Rect>(*rect);
}

size_t BasicRenderComponent::getLayer() const {
  return layer;
}

void BasicRenderComponent::setModelTransform(NVGcontext *const ctx) {
  nvgTransform(ctx, getEntity().get<AnimationComponent>()->getModelMat());
}
