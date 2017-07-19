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
#include <glm/gtx/norm.hpp>

Player::Player()
  : rect(0, 0, 1, 1) {}

void Player::startMoving(const Math::Dir dir) {
  motion[Math::ToNum<size_t>::conv(dir)] = true;
}

void Player::stopMoving(const Math::Dir dir) {
  motion[Math::ToNum<size_t>::conv(dir)] = false;
}

void Player::update(const float delta) {
  const float moveSpeed = 2.0f;
  
  glm::vec2 moveDir = {0.0f, 0.0f};
  moveDir += ToVec::conv(Math::Dir::UP,    static_cast<float>(motion[0]));
  moveDir += ToVec::conv(Math::Dir::RIGHT, static_cast<float>(motion[1]));
  moveDir += ToVec::conv(Math::Dir::DOWN,  static_cast<float>(motion[2]));
  moveDir += ToVec::conv(Math::Dir::LEFT,  static_cast<float>(motion[3]));
  
  if (glm::length2(moveDir) > 0.0f) {
    //diagonal motion has the same speed as orthogonal motion
    rect.p += glm::normalize(moveDir) * (delta * moveSpeed);
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
