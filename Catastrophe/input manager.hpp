//
//  input manager.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 11/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef input_manager_hpp
#define input_manager_hpp

#include <SDL2/SDL_events.h>
#include "input command.hpp"

class InputManager {
public:
  InputManager() = default;
  ~InputManager() = default;

  InputCommand::Ptr handleInput(SDL_Event);
};

#endif
