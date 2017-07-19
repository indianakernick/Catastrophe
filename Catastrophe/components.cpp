//
//  components.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "components.hpp"

RectComponent::RectComponent(const Rect rect)
  : rect(rect) {}

DirInputComponent::DirInputComponent(
  const SDL_Scancode upKey,
  const SDL_Scancode rightKey,
  const SDL_Scancode downKey,
  const SDL_Scancode leftKey
) : upKey(upKey),
    rightKey(rightKey),
    downKey(downKey),
    leftKey(leftKey) {}

MotionComponent::MotionComponent(const int speed)
  : freqLimiter(Time::OP_PER_SEC, speed),
    motionDir(Math::Dir::NONE),
    nextDir(Math::Dir::NONE) {}

AnimSpriteComponent::AnimSpriteComponent(const std::string &path)
  : path(path),
    progress(0.0f) {}
