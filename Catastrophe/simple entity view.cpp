//
//  simple entity view.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "simple entity view.hpp"

SimpleEntityView::SimpleEntityView(Entity *entity, const std::string &name)
  : LocalEntityView(entity), spriteName(name) {}

void SimpleEntityView::render(RenderingContext &ctx, uint64_t) {
  using ToVec = Math::ToVec<Rect::Scalar, Math::Dir::RIGHT, Math::Dir::DOWN>;
  Rect rect = getEntity().getRect();
  if (getEntity().isMoving()) {
    rect.p += ToVec::conv(getEntity().getMotionDir(), getEntity().getMotionProgress());
  }
  ctx.renderSprite(spriteName, rect);
}
