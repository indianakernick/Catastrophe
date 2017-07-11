//
//  input component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "input component.hpp"

void InputComponent::setMoveSpeed(const float newMoveSpeed) {
  moveSpeed = newMoveSpeed;
}

float InputComponent::getMoveSpeed() const {
  return moveSpeed;
}
