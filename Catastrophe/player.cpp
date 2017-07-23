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
#include "spawn bullet.hpp"
#include "rendering context.hpp"

Player::Player(const EntityID id, const GunSpec gunSpec, const glm::vec2 pos)
  : Entity(id, {pos, SIZE}), gun(gunSpec) {
  //just for debuging the gun
  gun.collectClips(4);
}

void Player::startMoving(const Math::Dir dir) {
  moveDir.start(dir);
}

void Player::stopMoving(const Math::Dir dir) {
  moveDir.stop(dir);
}

void Player::startShooting(const Math::Dir dir) {
  shootDir.start(dir);
  if (shootDir.get() != lastShootDir) {
    if (shootDir.get() == Math::Dir::NONE) {
      gun.stopFiring();
    } else if (lastShootDir == Math::Dir::NONE) {
      gun.startFiring();
    } else {
      gun.changeDir();
    }
    lastShootDir = shootDir.get();
  }
}

void Player::stopShooting(const Math::Dir dir) {
  shootDir.stop(dir);
  if (shootDir.get() != lastShootDir) {
    if (shootDir.get() == Math::Dir::NONE) {
      gun.stopFiring();
    } else {
      gun.changeDir();
    }
    lastShootDir = shootDir.get();
  }
}

void Player::reload() {
  gun.reload();
}

void Player::update(EntityManager &entityManager, const float delta) {
  if (moveDir.get() != Math::Dir::NONE) {
    const Rect prevRect = rect;
    rect.p += ToVec::conv(moveDir.get(), delta * MOVE_SPEED);
    movedFrom(prevRect);
  }
  
  gun.update(delta);
  
  spawnBullet(entityManager, gun, rect, shootDir.get());
}

void Player::render(RenderingContext &renderer) const {
  renderer.renderSprite("rat", rect);
}
