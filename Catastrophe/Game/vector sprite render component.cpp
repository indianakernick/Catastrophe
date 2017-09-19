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
#include "animation component.hpp"

VectorRenderComponent::VectorRenderComponent(
  Entity *const entity,
  const float width,
  const float height
) : RenderComponent(entity),
    rect(makeMotionTarget(glm::vec2(), glm::vec2(width, height))),
    size(makeZoomTarget(width, height)) {}
    
void VectorRenderComponent::render(NVGcontext *context) {
  const auto anim = getEntity().animation;
  rect->c = anim->getModelMat()[2];
  renderSprite(
    context,
    anim->getShapes(),
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
