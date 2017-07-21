//
//  player.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "player.hpp"

#include "dir to vec.hpp"
#include "player constants.hpp"
#include "rendering context.hpp"

Player::Player()
  : Entity({0, 0, 1, 1}) {}

void Player::startMoving(const Math::Dir dir) {
  moveDir.start(dir);
}

void Player::stopMoving(const Math::Dir dir) {
  moveDir.stop(dir);
}

void Player::update(const float delta) {
  if (moveDir.get() != Math::Dir::NONE) {
    const Rect prevRect = rect;
    rect.p += ToVec::conv(moveDir.get(), delta * PLAYER_MOVE_SPEED);
    movedFrom(prevRect);
  }
}

void Player::render(RenderingContext &renderer) const {
  renderer.renderSprite("rat", rect);
}
