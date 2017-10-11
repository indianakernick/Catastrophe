//
//  button physics component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 5/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "button physics component.hpp"

void ButtonPhysicsComponent::beginContactingPlayer() {
  contacting = true;
}

void ButtonPhysicsComponent::endContactingPlayer() {
  contacting = false;
}

bool ButtonPhysicsComponent::playerOnButton() const {
  return contacting;
}
