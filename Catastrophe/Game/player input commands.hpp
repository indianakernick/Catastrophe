//
//  player input commands.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef player_input_commands_hpp
#define player_input_commands_hpp

#include "input commands.hpp"

class PlayerInputCommands final : public InputCommands {
public:
  bool moveLeft = false;
  bool moveRight = false;
  bool jump = false;
};

#endif
