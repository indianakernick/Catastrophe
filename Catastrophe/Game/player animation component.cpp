//
//  player animation component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "player animation component.hpp"

#include "b2 glm cast.hpp"
#include "vector render.hpp"
#include "player physics state.hpp"
#include <Simpleton/Math/scale.hpp>
#include "vector rendering state.hpp"
#include <glm/gtx/matrix_transform_2d.hpp>

PlayerAnimationComponent::PlayerAnimationComponent(const Sprite &sprite)
  : sprite(sprite), anim(sprite.animations.at("run").durationSec) {}

void PlayerAnimationComponent::update(
  RenderingState &rendering,
  const PhysicsState &physics,
  const float delta
) {
  VectorRenderingState &vectorRender = dynamic_cast<VectorRenderingState &>(rendering);
  const PlayerPhysicsState &playerPhysics = dynamic_cast<const PlayerPhysicsState &>(physics);
  
  vectorRender.shapes = sprite.shapes;
  
  const float horiVel = playerPhysics.vel.x;
  anim.advance(delta * Math::abs(horiVel / PLAYER_FOOT_SPEED));
  anim.repeatOnOverflow();
  
  vectorRender.frame = getFrame(sprite, "run", anim.getProgress<float>());
  
  const float horiScale = Math::sign(horiVel);
  vectorRender.modelMat = glm::translate({}, castToGLM(physics.pos));
  vectorRender.modelMat = glm::scale(vectorRender.modelMat, {horiScale, 1.0f});
}
