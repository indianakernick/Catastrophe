//
//  player render component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "player render component.hpp"

#include "entity.hpp"
#include "vector file.hpp"
#include "yaml helper.hpp"
#include "vector render.hpp"
#include "player animation component.hpp"
#include <Simpleton/Utils/safe down cast.hpp>

PlayerRenderComponent::PlayerRenderComponent(
  const YAML::Node &node,
  const YAML::Node &level
) : BasicRenderComponent(node, level),
    spriteName(getChild(node, "sprite").Scalar()) {}

void PlayerRenderComponent::init(NVGcontext *, RenderResMan &resMan) {
  sprite = loadSprite(spriteName, resMan);
}

void PlayerRenderComponent::render(NVGcontext *const ctx) {
  const auto animComp = Utils::safeDownCast<PlayerAnimationComponent>(
    getEntity().animation
  );
  
  const float leg = animComp->getRightLeg() ? 1.0f : 0.0f;
  
  Frame frame = ::getFrame(sprite, "stand", leg);
  lerpFrames(
    animComp->getGroundJumpProg(),
    frame,
    ::getFrame(sprite, "stand jump", leg)
  );
  
  Frame runningFrame = ::getFrame(sprite, "run", animComp->getRunningProg());
  lerpFrames(
    animComp->getGroundJumpProg(),
    runningFrame,
    ::getFrame(sprite, "run jump", leg)
  );
  
  lerpFrames(
    animComp->getStandRunProg(),
    frame,
    runningFrame
  );
  
  setModelTransform(ctx);
  renderSprite(ctx, sprite, frame);
}
