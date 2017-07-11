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
#include "input command.hpp"

class GameLogic {
public:
  GameLogic();
  
  void init();
  void quit();
  void handleCommand(InputCommand::Ptr);
  void update(uint64_t);
  
private:
  Actor player;
};

#endif
