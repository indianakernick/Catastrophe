//
//  simple animation component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 17/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "simple animation component.hpp"

#include "entity.hpp"
#include "yaml helper.hpp"
#include "vector file.hpp"
#include "vector render.hpp"
#include "physics component.hpp"
#include <glm/gtx/matrix_transform_2d.hpp>
#include <Simpleton/Utils/safe down cast.hpp>

SimpleAnimationComponent::SimpleAnimationComponent(
  const YAML::Node &node,
  const YAML::Node &level,
  RenderingContext &renderer
) {
  sprite = loadSprite(getChild(node, "sprite").Scalar(), renderer);
  transform.scale = readGLMvec(getChild(level, "scale"));
  anim.setDuration(sprite.animations.at("main").durationSec);
}

void SimpleAnimationComponent::update(const float delta) {
  anim.advance(delta);
  anim.repeatOnOverflow();
  frame = ::getFrame(sprite, "main", anim.getProgressTime());
  transform.pos = getEntity().physics->getPos();
  transform.rotation = getEntity().physics->getAngle();
  model = transform.getMat3();
}

const Sprite &SimpleAnimationComponent::getSprite() const {
  return sprite;
}

const Frame &SimpleAnimationComponent::getFrame() const {
  return frame;
}

glm::mat3 SimpleAnimationComponent::getModelMat() const {
  return model;
}
