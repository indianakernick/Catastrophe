//
//  vector render component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 3/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "vector render component.hpp"

#include "entity.hpp"
#include "yaml helper.hpp"
#include "vector render.hpp"
#include "animation component.hpp"

VectorRenderComponent::VectorRenderComponent(
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
  rect = makeMotionTarget(glm::vec2(), scale);
  size = makeZoomTarget(scale);
}

void VectorRenderComponent::preRender() {
  rect->c = getEntity().animation->getModelMat()[2];
}

void VectorRenderComponent::render(NVGcontext *context) {
  const auto anim = getEntity().animation;
  renderSprite(
    context,
    anim->getSprite(),
    anim->getFrame(),
    anim->getModelMat()
  );
}

CameraMotionTargetCPtr VectorRenderComponent::getMotionTarget() const {
  return rect;
}

CameraZoomTargetCPtr VectorRenderComponent::getZoomTarget() const {
  return size;
}

Rect VectorRenderComponent::getAABB() const {
  return static_cast<Rect>(*rect);
}
