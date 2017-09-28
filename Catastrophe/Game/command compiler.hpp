//
//  command compiler.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 24/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef command_compiler_hpp
#define command_compiler_hpp

#include "parse string.hpp"
#include "vector sprite.hpp"

class CommandCompilerError final : public std::runtime_error {
public:
  explicit CommandCompilerError(const std::string &);
};

DrawCommands compileDrawCommands(const std::string &, FrameSize, LineCol);

#endif
