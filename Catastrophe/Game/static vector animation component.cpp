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
#include "vector rendering state.hpp"
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
  auto &vectorRender = dynamic_cast<VectorRenderingState &>(*getEntity().latestRenderingState);
  
  vectorRender.shapes = sprite.shapes;
  vectorRender.frame = getFrame(sprite, "static", 0.0f);
  vectorRender.modelMat = glm::translate({}, getEntity().physics->getPos());
  vectorRender.modelMat = glm::scale(vectorRender.modelMat, scale);
}
