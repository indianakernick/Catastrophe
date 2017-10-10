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
#include "rendering context.hpp"
#include "animation component.hpp"

void VectorSpriteRenderComponent::init(RenderingContext &renderer, const YAML::Node &node) {
  BasicRenderComponent::init(renderer, node);
  sprite = loadSprite(getChild(node, "sprite").Scalar(), renderer.getResources());
}

void VectorSpriteRenderComponent::render(NVGcontext *const ctx) {
  const auto animComp = getEntity().animation;
  nvgTransform(ctx, animComp->getModelMat());
  renderSprite(ctx, sprite, getFrame(sprite, "main", animComp->getProgress()));
}
