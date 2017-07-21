//
//  bullet.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "bullet.hpp"

#include "dir to vec.hpp"
#include "rendering context.hpp"

Bullet::Bullet(const glm::vec2 pos, const Math::Dir dir)
  : Entity({pos, BULLET_SIZE}), dir(dir) {}

void Bullet::update(EntityManager &, const float delta) {
  rect.p += ToVec::conv(dir, delta * MOVE_SPEED);
}

void Bullet::render(RenderingContext &renderingContext) const {
  renderingContext.renderSprite("small rat", rect);
}
