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

void DirQueue::push(const Math::Dir dir) {
  queue.push_front(dir);
  calcDir();
}

void DirQueue::pop(const Math::Dir dir) {
  for (auto d = queue.cbegin(); d != queue.cend(); ++d) {
    if (*d == dir) {
      queue.erase(d);
      calcDir();
      break;
    }
  }
}

Math::Dir DirQueue::getDir() const {
  return dir;
}

void DirQueue::calcDir() {
  size_t horiCount = 0;
  for (auto d = queue.cbegin(); d != queue.cend(); ++d) {
    horiCount += static_cast<size_t>(Math::getAxis(*d));
  }
  const bool couldBeHori = horiCount == 1;
  const bool couldBeVert = queue.size() - horiCount == 1;
  
  for (auto d = queue.cbegin(); d != queue.cend(); ++d) {
    if ((Math::isHori(*d) && couldBeHori) || (Math::isVert(*d) && couldBeVert)) {
      dir = *d;
      return;
    }
  }
  dir = Math::Dir::NONE;
}

Player::Player()
  : rect(0, 0, 1, 1) {}

void Player::startMoving(const Math::Dir dir) {
  dirQueue.push(dir);
}

void Player::stopMoving(const Math::Dir dir) {
  dirQueue.pop(dir);
}

void Player::update(const float delta) {
  const float moveSpeed = 0.5f;
  
  if (dirQueue.getDir() != Math::Dir::NONE) {
    rect.p += ToVec::conv(dirQueue.getDir(), delta * moveSpeed);
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
