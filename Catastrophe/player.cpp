//
//  player.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "player.hpp"

#include "constants.hpp"
#include "dir to vec.hpp"

Player::Player()
  : rect(0, 0, 1, 1),
    moveDir(Math::Dir::NONE) {}

void Player::startMoving(const Math::Dir dir) {
  moveDir = dir;
}

void Player::stopMoving() {
  moveDir = Math::Dir::NONE;
}

void Player::update(const float delta) {
  if (moveDir != Math::Dir::NONE) {
    const float moveSpeed = 1.0f;//units per second
    rect.p += ToVec::conv(moveDir, delta * moveSpeed);
  }
}

void Player::render(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  const SDL_Rect dst = {
    static_cast<int>(rect.p.x * PIXELS_PER_TILE.x),
    static_cast<int>(rect.p.y * PIXELS_PER_TILE.y),
    static_cast<int>(rect.s.x * PIXELS_PER_TILE.x),
    static_cast<int>(rect.s.y * PIXELS_PER_TILE.y)
  };
  SDL_RenderFillRect(renderer, &dst);
}
