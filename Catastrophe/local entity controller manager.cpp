//
//  local entity controller manager.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 12/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "local entity controller manager.hpp"

bool LocalEntityControllerManager::handleEvent(const SDL_Event event) {
  #define DISPATCH_EVENT(METHOD, MEMBER)                                          \
    for (auto c = controllers.cbegin(); c != controllers.cend(); ++c) {         \
      if ((*c)->on##METHOD(event.MEMBER)) {                                     \
        return true;                                                            \
      }                                                                         \
    } do{}while(0)
  
  switch (event.type) {
    case SDL_KEYDOWN:
      DISPATCH_EVENT(KeyDown, key);
      break;
    case SDL_KEYUP:
      DISPATCH_EVENT(KeyUp, key);
      break;
    case SDL_MOUSEBUTTONDOWN:
      DISPATCH_EVENT(MouseDown, button);
      break;
    case SDL_MOUSEBUTTONUP:
      DISPATCH_EVENT(MouseUp, button);
      break;
    case SDL_MOUSEMOTION:
      DISPATCH_EVENT(MouseMove, motion);
      break;
  }
  
  #undef DISPATCH_EVENT
  
  return false;
}

void LocalEntityControllerManager::addController(std::shared_ptr<LocalEntityController> controller) {
  controllers.push_back(controller);
}
