//
//  input commands.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 11/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef input_commands_hpp
#define input_commands_hpp

#include "input command.hpp"

class MoveCommand : public InputCommand {
public:
  explicit MoveCommand(Math::Dir);
  
  void execute(Actor &) override;
  
private:
  Math::Dir dir;
};

#endif
