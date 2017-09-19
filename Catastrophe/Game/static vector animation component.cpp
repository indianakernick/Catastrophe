//
//  static vector animation component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 17/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "static vector animation component.hpp"

#include "b2 glm cast.hpp"
#include "vector render.hpp"
#include "physics state.hpp"
#include "vector rendering state.hpp"
#include <glm/gtx/matrix_transform_2d.hpp>

StaticVectorAnimationComponent::StaticVectorAnimationComponent(
  Entity *const entity,
  const Sprite &sprite,
  const glm::vec2 scale
) : AnimationComponent(entity),
    sprite(sprite),
    scale(scale) {}

void StaticVectorAnimationComponent::update(
  RenderingState &rendering,
  const PhysicsState &physics,
  float
) {
  VectorRenderingState &vectorRender = dynamic_cast<VectorRenderingState &>(rendering);
  
  vectorRender.shapes = sprite.shapes;
  vectorRender.frame = getFrame(sprite, "static", 0.0f);
  vectorRender.modelMat = glm::translate({}, castToGLM(physics.pos));
  vectorRender.modelMat = glm::scale(vectorRender.modelMat, scale);
}
