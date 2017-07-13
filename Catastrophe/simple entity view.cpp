//
//  simple entity view.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "simple entity view.hpp"

#include "dir to vec.hpp"
#include "ortho move entity.hpp"

SimpleEntityView::SimpleEntityView(Entity *entity, const std::string &name)
  : LocalEntityView(entity), spriteName(name) {}

void SimpleEntityView::render(RenderingContext &ctx, uint64_t) {
  const OrthoMoveEntity &entity = dynamic_cast<OrthoMoveEntity &>(getEntity());
  Rect rect = getEntity().getRect();
  if (entity.isMoving()) {
    rect.p += ToVec::conv(entity.getMotionDir(), entity.getMotionProgress());
  }
  ctx.renderSprite(spriteName, rect);
}
