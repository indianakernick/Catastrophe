//
//  handle input.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "handle input.hpp"

#include <Simpleton/Event/manager.hpp>
#include "player move event.hpp"
#include <iostream>

void handleGameInput(const SDL_Event &event) {
  if (event.type == SDL_KEYDOWN) {
    switch (event.key.keysym.scancode) {
      case SDL_SCANCODE_W:
        evtMan->emit<PlayerMoveEvent>(Math::Dir::UP);
        break;
      case SDL_SCANCODE_D:
        evtMan->emit<PlayerMoveEvent>(Math::Dir::RIGHT);
        break;
      case SDL_SCANCODE_S:
        evtMan->emit<PlayerMoveEvent>(Math::Dir::DOWN);
        break;
      case SDL_SCANCODE_A:
        evtMan->emit<PlayerMoveEvent>(Math::Dir::LEFT);
        break;
      
      default: ;
    }
  }
}
