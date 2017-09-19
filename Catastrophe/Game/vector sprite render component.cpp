//
//  vector sprite render component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 3/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "vector sprite render component.hpp"

#include "entity.hpp"
#include "vector render.hpp"
#include "vector rendering state.hpp"

VectorRenderComponent::VectorRenderComponent(
  Entity *const entity,
  const float width,
  const float height
) : RenderComponent(entity),
    rect(std::make_shared<CameraMotionTarget>(glm::vec2(), glm::vec2(width, height))),
    size(std::make_shared<CameraZoomTarget>(width, height)) {}
    
void VectorRenderComponent::render(NVGcontext *context) {
  const auto &vectorRender = dynamic_cast<const VectorRenderingState &>(*getEntity().latestRenderingState);
  rect->c = vectorRender.modelMat[2];
  renderSprite(context, vectorRender.shapes, vectorRender.frame, vectorRender.modelMat);
}

std::shared_ptr<const CameraMotionTarget> VectorRenderComponent::getMotionTarget() const {
  return rect;
}

std::shared_ptr<const CameraZoomTarget> VectorRenderComponent::getZoomTarget() const {
  return size;
}

Rect VectorRenderComponent::getAABB() const {
  return static_cast<Rect>(*rect);
}
