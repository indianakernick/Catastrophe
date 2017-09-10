//
//  simple animation component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "simple animation component.hpp"

#include "b2 glm cast.hpp"
#include "physics state.hpp"
#include "rendering state.hpp"
#include <glm/gtx/matrix_transform_2d.hpp>

void SimpleAnimationComponent::update(RenderingState &rendering, const PhysicsState &physics, float) {
  rendering.modelMat = glm::translate({}, castToGLM(physics.pos));
}
