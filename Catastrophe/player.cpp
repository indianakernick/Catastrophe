//
//  player.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "player.hpp"

#include "window constants.hpp"
#include "player constants.hpp"
#include "dir to vec.hpp"
#include <SDL2/SDL_render.h>

Player::Player()
  : rect(0, 0, 1, 1) {}

void Player::startMoving(const Math::Dir dir) {
  moveDir.start(dir);
}

void Player::stopMoving(const Math::Dir dir) {
  moveDir.stop(dir);
}

void Player::update(const float delta) {
  if (moveDir.get() != Math::Dir::NONE) {
    rect.p += ToVec::conv(moveDir.get(), delta * PLAYER_MOVE_SPEED);
  }
}

void Player::render(SDL_Renderer *renderer) const {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  const SDL_Rect dst = {
    static_cast<int>(rect.p.x * PIXELS_PER_TILE.x),
    static_cast<int>(rect.p.y * PIXELS_PER_TILE.y),
    static_cast<int>(rect.s.x * PIXELS_PER_TILE.x),
    static_cast<int>(rect.s.y * PIXELS_PER_TILE.y)
  };
  SDL_RenderFillRect(renderer, &dst);
}
