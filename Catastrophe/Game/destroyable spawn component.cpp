//
//  destroyable spawn component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "destroyable spawn component.hpp"

void DestroyableSpawnComponent::init(const YAML::Node &node) {
  if (const YAML::Node timeLeftNode = node["max lifetime"]) {
    timeLeft = timeLeftNode.as<float>();
  } else {
    timeLeft = std::numeric_limits<float>::infinity();
  }
}

void DestroyableSpawnComponent::update(const float delta) {
  timeLeft -= delta;
  if (timeLeft < 0.0f) {
    dead = true;
  }
}

bool DestroyableSpawnComponent::shouldDestroySelf() const {
  return dead;
}

void DestroyableSpawnComponent::kill() {
  dead = true;
}
