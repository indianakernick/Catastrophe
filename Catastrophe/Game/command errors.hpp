//
//  command errors.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef command_errors_hpp
#define command_errors_hpp

#include <stdexcept>

class DrawCommandError final : public std::runtime_error {
public:
  explicit DrawCommandError(const char *);
};

class CommandCompilerError final : public std::runtime_error {
public:
  explicit CommandCompilerError(const std::string &);
};

#endif
