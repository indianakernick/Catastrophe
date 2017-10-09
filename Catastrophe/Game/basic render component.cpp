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

BasicRenderComponent::BasicRenderComponent(
  const YAML::Node &node,
  const YAML::Node &level
) {
  glm::vec2 scale = {1.0f, 1.0f};
  if (const YAML::Node &sizeNode = node["scale"]) {
    scale = readGLMvec(sizeNode);
  }
  if (const YAML::Node &sizeNode = level["scale"]) {
    scale = readGLMvec(sizeNode);
  }
  layer = 0;
  if (const YAML::Node &layerNode = node["layer"]) {
    layer = getLayerIndex(layerNode.Scalar());
  }
  if (const YAML::Node &layerNode = level["layer"]) {
    layer = getLayerIndex(layerNode.Scalar());
  }
  rect = makeMotionTarget(glm::vec2(), scale);
  size = makeZoomTarget(scale);
}

void BasicRenderComponent::init(NVGcontext *, RenderResMan &) {}

void BasicRenderComponent::preRender() {
  rect->c = getEntity().animation->getModelMat()[2];
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
  nvgTransform(ctx, getEntity().animation->getModelMat());
}
