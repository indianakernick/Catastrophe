//
//  game logic.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_logic_hpp
#define game_logic_hpp

#include "actor.hpp"
#include <SDL2/SDL_events.h>

class GameLogic {
public:
  
  void init();
  void quit();
  void handleInput(const SDL_Event &);
  void update(uint64_t);
  
private:
  Actor player;
};

#endif
