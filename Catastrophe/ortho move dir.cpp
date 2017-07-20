//
//  ortho move dir.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 20/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "ortho move dir.hpp"

void OrthoMoveDir::start(const Math::Dir dir) {
  queue.push_front(dir);
  calcDir();
}

void OrthoMoveDir::stop(const Math::Dir dir) {
  for (auto d = queue.cbegin(); d != queue.cend(); ++d) {
    if (*d == dir) {
      queue.erase(d);
      calcDir();
      break;
    }
  }
}

Math::Dir OrthoMoveDir::get() const {
  return dir;
}

void OrthoMoveDir::calcDir() {
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
