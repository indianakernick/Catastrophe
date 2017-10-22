//
//  destroyable spawn component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "destroyable spawn component.hpp"

void DestroyableSpawnComponent::init(const YAML::Node &) {}

void DestroyableSpawnComponent::update(float) {}

bool DestroyableSpawnComponent::shouldDestroySelf() const {
  return dead;
}

void DestroyableSpawnComponent::kill() {
  dead = true;
}
