//
//  input system.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "input system.hpp"

#include <SDL2/SDL_events.h>
#include "input component.hpp"
#include <Simpleton/Utils/profiler.hpp>

void InputSystem::add(const EntityID id, const CompPtr comp, const YAML::Node &node) {
  comp->init(node);
  components.emplace(id, comp);
}

void InputSystem::rem(const EntityID id) {
  components.erase(id);
}

void InputSystem::handleEvent(const SDL_Event event, const glm::mat3 toMeters) {
  PROFILE(InputSystem handleEvent);
  
  for (auto c = components.cbegin(); c != components.cend(); ++c) {
    if (c->second->handleEvent(event, toMeters)) {
      break;
    }
  }
}
