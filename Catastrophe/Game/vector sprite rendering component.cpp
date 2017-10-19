//
//  vector sprite rendering component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "vector sprite rendering component.hpp"

#include "entity.hpp"
#include "nvg helper.hpp"
#include "yaml helper.hpp"
#include "vector file.hpp"
#include "vector render.hpp"
#include "rendering context.hpp"
#include "animation component.hpp"

void VectorSpriteRenderingComponent::init(RenderingContext &renderer, const YAML::Node &node) {
  BasicRenderingComponent::init(renderer, node);
  sprite = loadSprite(getChild(node, "sprite").Scalar(), renderer.getResources());
}

void VectorSpriteRenderingComponent::render(NVGcontext *const ctx) {
  const auto animComp = getExpectedComp<AnimationComponent>();
  nvgTransform(ctx, animComp->getModelMat());
  renderSprite(ctx, sprite, getFrame(sprite, "main", animComp->getProgress()));
}
