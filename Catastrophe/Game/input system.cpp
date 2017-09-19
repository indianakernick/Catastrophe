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

void InputSystem::add(const EntityID id, const std::shared_ptr<InputComponent> comp) {
  components.emplace(id, comp);
}

void InputSystem::rem(const EntityID id) {
  components.erase(id);
}

void InputSystem::handleEvent(const SDL_Event event) {
  if (dispatcher.dispatch(event)) {
    return;
  }
  
  for (auto c = components.cbegin(); c != components.cend(); ++c) {
    if (c->second->handleEvent(event)) {
      break;
    }
  }
}

InputSystem::ListenerID InputSystem::addListener(const Listener &listener) {
  return dispatcher.addListener(listener);
}

void InputSystem::remListener(const ListenerID id) {
  dispatcher.remListener(id);
}
