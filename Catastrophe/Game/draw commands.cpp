//
//  draw commands.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 24/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "draw commands.hpp"

DrawCommandError::DrawCommandError(const char *what)
  : std::runtime_error(what) {}

//I pulled the next 2 functions out of the command interpreter for
//my password manager. It's on Github

Index readNumber(std::experimental::string_view &args) {
  if (args.empty()) {
    throw DrawCommandError("Expected number");
  }
  char *end;
  const unsigned long long arg = std::strtoull(args.data(), &end, 0);
  if (errno == ERANGE || arg > std::numeric_limits<Index>::max()) {
    throw DrawCommandError("Number out of range");
  }
  if (arg == 0 && end[-1] != '0') {
    throw DrawCommandError("Invalid number");
  }
  args.remove_prefix(end - args.data());
  return static_cast<Index>(arg);
}

std::string readString(std::experimental::string_view &args) {
  if (args.empty()) {
    throw DrawCommandError("Expected string");
  }
  
  size_t begin = 0;
  for (; begin != args.size(); ++begin) {
    if (args[begin] != ' ') {
      break;
    }
  }
  
  if (begin == args.size()) {
    throw DrawCommandError("Expected string");
  }
  
  size_t end = 0;
  std::string arg;
  
  for (end = begin; end != args.size(); ++end) {
    const char c = args[end];
    if (std::isspace(c)) {
      break;
    } else {
      arg.push_back(c);
    }
  }
  
  args.remove_prefix(end);
  
  return arg;
}

void checkIndex(const Index index, const Index size) {
  if (index >= size) {
    throw DrawCommandError("Index out of range");
  }
}
