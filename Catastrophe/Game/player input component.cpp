//
//  player input component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "player input component.hpp"

#include "input file.hpp"
#include "yaml helper.hpp"
#include <SDL2/SDL_events.h>

namespace {
  void getOptional(SDL_Scancode &code, const KeyBindings &bindings, const char *name) {
    auto iter = bindings.find(name);
    if (iter != bindings.cend()) {
      code = iter->second;
    }
  }
}

void PlayerInputComponent::init(const YAML::Node &node) {
  const KeyBindings bindings = loadInputs(getChild(node, "keys").Scalar());
  getOptional(leftKey, bindings, "left");
  getOptional(rightKey, bindings, "right");
  getOptional(jumpKey, bindings, "jump");
}

bool PlayerInputComponent::handleEvent(const SDL_Event event, glm::mat3) {
  if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
    return handleKey(event.key.keysym.scancode, true);
  } else if (event.type == SDL_KEYUP) {
    return handleKey(event.key.keysym.scancode, false);
  } else {
    return false;
  }
}

bool PlayerInputComponent::shouldMoveLeft() const {
  return leftButton && !rightButton;
}

bool PlayerInputComponent::shouldMoveRight() const {
  return rightButton && !leftButton;
}

bool PlayerInputComponent::shouldJump() const {
  return jumpButton;
}

bool PlayerInputComponent::handleKey(const SDL_Scancode key, const bool down) {
         if (key == leftKey) {
    leftButton = down;
    return true;
  } else if (key == rightKey) {
    rightButton = down;
    return true;
  } else if (key == jumpKey) {
    jumpButton = down;
    return true;
  } else {
    return false;
  }
}
