//
//  physics component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "physics component.hpp"

#include <stdexcept>

PhysicsComponent::PhysicsComponent(b2Body *const body)
  : body(body) {
  if (body == nullptr) {
    throw std::runtime_error("Null physics body passed to PhysicsComponent");
  }
}
