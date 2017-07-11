//
//  input command.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 11/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef input_command_hpp
#define input_command_hpp

#include <memory>
#include "actor.hpp"

class InputCommand {
public:
  using Ptr = std::shared_ptr<InputCommand>;

  InputCommand() = default;
  virtual ~InputCommand() = default;
  
  virtual void execute(Actor &) = 0;
  
};

#endif
