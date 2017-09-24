//
//  command compiler.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 24/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "command compiler.hpp"

DrawCommands compileDrawCommands(const std::string &string) {
  DrawCommands commands;
  commands.reserve(string.size() / 8);
  
  return commands;
}
