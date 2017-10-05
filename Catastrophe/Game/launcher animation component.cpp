//
//  launcher animation component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 5/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "launcher animation component.hpp"

#include "yaml helper.hpp"
#include "vector file.hpp"
#include "vector render.hpp"
#include "systems registry.hpp"
#include "launcher physics component.hpp"
#include <Simpleton/Utils/safe down cast.hpp>

LauncherAnimationComponent::LauncherAnimationComponent(
  const YAML::Node &node,
  const YAML::Node &
) {
  sprite = loadSprite(getChild(node, "sprite").Scalar(), *Systems::renderer);
}

void LauncherAnimationComponent::update(float) {
  const auto physics = Utils::safeDownCast<LauncherPhysicsComponent>(getEntity().physics);
  frame = ::getFrame(sprite, "main", physics->getRelTranslation());
  Transform transform;
  transform.pos = physics->getCenter();
  //the sprite is pointing in the +y direction but getRotation returns an angle
  //relative to the +x direction so we subtract a quarter turn
  transform.rotation = physics->getRotation() - (b2_pi / 2);
  transform.scale = glm::vec2(physics->getLimitSize());
  model = transform.getMat3();
}

const Sprite &LauncherAnimationComponent::getSprite() const {
  return sprite;
}

const Frame &LauncherAnimationComponent::getFrame() const {
  return frame;
}

glm::mat3 LauncherAnimationComponent::getModelMat() const {
  return model;
}
