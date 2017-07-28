//
//  ortho move dir.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 20/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "ortho move dir.hpp"

void OrthoMoveDir::start(const Math::Dir dir) {
  const Math::Dir opDir = Math::opposite(dir);
  if (curr == opDir || prev == opDir) {
    if (curr == opDir) {
      curr = prev;
    }
    prev = Math::Dir::NONE;
    hold[static_cast<size_t>(Math::getAxis(dir))] = true;
  } else {
    prev = curr;
    curr = dir;
  }
}

void OrthoMoveDir::stop(const Math::Dir dir) {
  const size_t holdIndex = static_cast<size_t>(Math::getAxis(dir));
  if (hold[holdIndex]) {
    (curr == Math::Dir::NONE ? curr : prev) = Math::opposite(dir);
    hold[holdIndex] = false;
  } else {
    if (prev != dir) {
      curr = prev;
    }
    prev = Math::Dir::NONE;
  }
}

Math::Dir OrthoMoveDir::get() const {
  return curr;
}
