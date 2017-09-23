//
//  static animation component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 17/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "static animation component.hpp"

#include "entity.hpp"
#include "vector render.hpp"
#include "physics component.hpp"
#include <glm/gtx/matrix_transform_2d.hpp>
#include <Simpleton/Utils/safe down cast.hpp>

StaticAnimationComponent::StaticAnimationComponent(
  Entity *const entity,
  const Sprite &sprite,
  const Transform transform
) : AnimationComponent(entity),
    sprite(sprite),
    transform(transform) {}

void StaticAnimationComponent::update(float) {
  frame = ::getFrame(sprite, "static", 0.0f);
  transform.pos = getEntity().physics->getPos();
  transform.rotation = getEntity().physics->getAngle();
  model = transform.getMat3();
}

const Shapes &StaticAnimationComponent::getShapes() const {
  return sprite.shapes;
}

const Frame &StaticAnimationComponent::getFrame() const {
  return frame;
}

glm::mat3 StaticAnimationComponent::getModelMat() const {
  return model;
}
