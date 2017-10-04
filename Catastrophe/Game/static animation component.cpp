//
//  static animation component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 17/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "static animation component.hpp"

#include "entity.hpp"
#include "yaml helper.hpp"
#include "vector file.hpp"
#include "vector render.hpp"
#include "physics component.hpp"
#include <glm/gtx/matrix_transform_2d.hpp>
#include <Simpleton/Utils/safe down cast.hpp>

StaticAnimationComponent::StaticAnimationComponent(
  const YAML::Node &node,
  const YAML::Node &level,
  RenderingContext &renderer
) {
  sprite = loadSprite(getChild(node, "sprite").Scalar(), renderer);
  transform.scale = readGLMvec(getChild(level, "scale"));
}

void StaticAnimationComponent::update(float) {
  frame = ::getFrame(sprite, "static", 0.0f);
  transform.pos = getEntity().physics->getPos();
  transform.rotation = getEntity().physics->getAngle();
  model = transform.getMat3();
}

const Sprite &StaticAnimationComponent::getSprite() const {
  return sprite;
}

const Frame &StaticAnimationComponent::getFrame() const {
  return frame;
}

glm::mat3 StaticAnimationComponent::getModelMat() const {
  return model;
}
