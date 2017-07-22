//
//  bullet.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "bullet.hpp"

#include "dir to vec.hpp"
#include "entity manager.hpp"
#include "rendering context.hpp"

Bullet::Bullet(
  const EntityID id,
  const BulletSpec spec,
  const glm::vec2 pos,
  const Math::Dir dir
) : Entity(id, {pos, SIZE}),
    spec(spec),
    timeTillDeath(LIFE_TIME),
    dir(dir) {}

void Bullet::update(EntityManager &entityManager, const float delta) {
  timeTillDeath -= delta;
  if (timeTillDeath <= 0.0f) {
    entityManager.kill(getID());
  }
  rect.p += ToVec::conv(dir, delta * spec.speed);
}

void Bullet::render(RenderingContext &renderingContext) const {
  renderingContext.renderSprite("small rat", rect);
}
