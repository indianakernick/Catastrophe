//
//  command errors.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "command errors.hpp"

DrawCommandError::DrawCommandError(const char *what)
  : std::runtime_error(what) {}

CommandCompilerError::CommandCompilerError(const std::string &what)
  : std::runtime_error(what) {}
