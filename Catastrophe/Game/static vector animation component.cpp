//
//  static vector animation component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 17/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "static vector animation component.hpp"

#include "entity.hpp"
#include "vector render.hpp"
#include "physics component.hpp"
#include <glm/gtx/matrix_transform_2d.hpp>
#include <Simpleton/Utils/safe down cast.hpp>

StaticVectorAnimationComponent::StaticVectorAnimationComponent(
  Entity *const entity,
  const Sprite &sprite,
  const glm::vec2 scale
) : AnimationComponent(entity),
    sprite(sprite),
    scale(scale) {}

void StaticVectorAnimationComponent::update(float) {
  frame = ::getFrame(sprite, "static", 0.0f);
  model = glm::scale(
    glm::translate(
      {},
      getEntity().physics->getPos()
    ),
    scale
  );
}

const Shapes &StaticVectorAnimationComponent::getShapes() const {
  return sprite.shapes;
}

const Frame &StaticVectorAnimationComponent::getFrame() const {
  return frame;
}

glm::mat3 StaticVectorAnimationComponent::getModelMat() const {
  return model;
}
