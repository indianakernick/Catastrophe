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
  if (currDir == Math::opposite(dir)) {
    currDir = prevDir;
    prevDir = Math::Dir::NONE;
    holding[static_cast<size_t>(Math::getAxis(dir))] = true;
  } else if (prevDir == Math::opposite(dir)) {
    prevDir = Math::Dir::NONE;
    holding[static_cast<size_t>(Math::getAxis(dir))] = true;
  } else {
    prevDir = currDir;
    currDir = dir;
  }
}

void Player::stopMoving(const Math::Dir dir) {
  if (holding[static_cast<size_t>(Math::getAxis(dir))]) {
    (currDir == Math::Dir::NONE ? currDir : prevDir) = Math::opposite(dir);
    holding[static_cast<size_t>(Math::getAxis(dir))] = false;
  } else {
    if (prevDir != dir) {
      currDir = prevDir;
    }
    prevDir = Math::Dir::NONE;
  }
}

void Player::printState() const {
  std::cout << "prevDir " << Math::ToString<true>::conv(prevDir) << '\n';
  std::cout << "currDir " << Math::ToString<true>::conv(currDir) << '\n';
  std::cout << std::boolalpha;
  std::cout << "holding " << holding[0] << ", " << holding[1] << '\n';
  std::cout << std::noboolalpha;//rdldrl
}

void Player::update(const float delta) {
  //using ToIndex = Math::ToNum<size_t>;

  const float moveSpeed = 0.5f;
  
  if (currDir != Math::Dir::NONE) {
    rect.p += ToVec::conv(currDir, delta * moveSpeed);
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
