//
//  player.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "player.hpp"

#include "bullet.hpp"
#include "dir to vec.hpp"
#include "entity manager.hpp"
#include "rendering context.hpp"

Player::Player(const EntityID id)
  : Entity(id, {{}, SIZE}) {}

Player::Player(const EntityID id, const glm::vec2 pos)
  : Entity(id, {pos, SIZE}) {}

void Player::startMoving(const Math::Dir dir) {
  moveDir.start(dir);
}

void Player::stopMoving(const Math::Dir dir) {
  moveDir.stop(dir);
}

void Player::startShooting(const Math::Dir dir) {
  shootDir.start(dir);
}

void Player::stopShooting(const Math::Dir dir) {
  shootDir.stop(dir);
}

void Player::update(EntityManager &entityManager, const float delta) {
  if (moveDir.get() != Math::Dir::NONE) {
    const Rect prevRect = rect;
    rect.p += ToVec::conv(moveDir.get(), delta * MOVE_SPEED);
    movedFrom(prevRect);
  }
  if (shootDir.get() != Math::Dir::NONE) {
    entityManager.make<Bullet>(rect.p + (SIZE - Bullet::SIZE) / 2.0f, shootDir.get());
  }
}

void Player::render(RenderingContext &renderer) const {
  renderer.renderSprite("rat", rect);
}
