//
//  vector sprite render component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "vector sprite render component.hpp"

#include "entity.hpp"
#include "nvg helper.hpp"
#include "yaml helper.hpp"
#include "vector file.hpp"
#include "vector render.hpp"
#include "animation component.hpp"

VectorSpriteRenderComponent::VectorSpriteRenderComponent(
  const YAML::Node &node,
  const YAML::Node &level
) : BasicRenderComponent(node, level),
    spriteName(getChild(node, "sprite").Scalar()) {}

void VectorSpriteRenderComponent::init(NVGcontext *, RenderResMan &resMan) {
  sprite = loadSprite(spriteName, resMan);
}

void VectorSpriteRenderComponent::render(NVGcontext *const ctx) {
  const auto animComp = getEntity().animation;
  nvgTransform(ctx, animComp->getModelMat());
  renderSprite(ctx, sprite, getFrame(sprite, "main", animComp->getProgress()));
}
