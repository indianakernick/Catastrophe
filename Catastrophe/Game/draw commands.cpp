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

Index readIndex(ParseString &string) {
  string.skipWhitespace();
  if (string.empty()) {
    throw DrawCommandError("Expected index");
  }
  //@TODO std::from_chars
  char *end;
  const unsigned long long arg = std::strtoull(string.data(), &end, 0);
  if (errno == ERANGE || arg > std::numeric_limits<Index>::max()) {
    throw DrawCommandError("Index out of range");
  }
  if (arg == 0 && end[-1] != '0') {
    throw DrawCommandError("Invalid index");
  }
  string.advance(end - string.data());
  return static_cast<Index>(arg);
}

float readFloat(ParseString &string) {
  string.skipWhitespace();
  if (string.empty()) {
    throw DrawCommandError("Expected float");
  }
  //@TODO std::from_chars
  char *end;
  const float arg = std::strtof(string.data(), &end);
  if (errno == ERANGE) {
    throw DrawCommandError("Float out of range");
  }
  string.advance(end - string.data());
  return arg;
}

glm::vec2 readPoint(ParseString &string) {
  glm::vec2 point;
  
  string.skipWhitespace();
  string.expect('[');
  point.x = readFloat(string);
  
  string.skipWhitespace();
  string.expect(',');
  point.y = readFloat(string);
  
  string.skipWhitespace();
  string.expect(']');
  
  return point;
}

void checkIndex(const Index index, const Index size) {
  if (index >= size) {
    throw DrawCommandError("Index out of range");
  }
}
