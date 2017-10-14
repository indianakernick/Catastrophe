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
#include "physics component.hpp"
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
  const AABB aabb = getAABB();
  *rect = static_cast<CameraMotionTarget>(aabb);
  *size = aabb.size();
}

CameraMotionTargetCPtr BasicRenderComponent::getMotionTarget() const {
  return rect;
}

CameraZoomTargetCPtr BasicRenderComponent::getZoomTarget() const {
  return size;
}

AABB BasicRenderComponent::getAABB() const {
  if (const auto physicsComp = getComp<PhysicsComponent>()) {
    return physicsComp->getAABB();
  } else if (const auto animComp = getComp<AnimationComponent>()) {
    const glm::mat3 modelMat = animComp->getModelMat();
    Math::RectCS<float> rectcs;
    rectcs.center = modelMat[2];
    rectcs.halfSize = {modelMat[0][0] / 2.0f, modelMat[1][1] / 2.0f};
    return static_cast<AABB>(rectcs);
  } else {
    return {};
  }
}

size_t BasicRenderComponent::getLayer() const {
  return layer;
}

void BasicRenderComponent::setModelTransform(NVGcontext *const ctx) {
  nvgTransform(ctx, getExpectedComp<AnimationComponent>()->getModelMat());
}
