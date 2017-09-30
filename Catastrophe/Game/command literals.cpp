//
//  command literals.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "command literals.hpp"

#include "command errors.hpp"

Index readIndex(Utils::ParseString &string, const Index size) {
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
  const Index index = static_cast<Index>(arg);
  if (index >= size) {
    throw DrawCommandError("Index out of range");
  }
  string.advance(end - string.data());
  return index;
}

float readFloat(Utils::ParseString &string) {
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

bool isLiteral(Utils::ParseString &string) {
  return string.front() == '[';
}

glm::vec2 readPoint(Utils::ParseString &string) {
  glm::vec2 point;
  
  string.expectAfterWhitespace('[');
  point.x = readFloat(string);
  
  string.expectAfterWhitespace(',');
  point.y = readFloat(string);
  
  string.expectAfterWhitespace(']');
  
  return point;
}

float readScalar(Utils::ParseString &string) {
  float scalar;
  
  string.expectAfterWhitespace('[');
  scalar = readFloat(string);
  
  string.expectAfterWhitespace(']');
  
  return scalar;
}

glm::vec4 readColor(Utils::ParseString &string) {
  glm::vec4 color;
  
  string.expectAfterWhitespace('[');
  color.r = readFloat(string);
  
  string.expectAfterWhitespace(',');
  color.g = readFloat(string);
  
  string.expectAfterWhitespace(',');
  color.b = readFloat(string);
  
  string.expectAfterWhitespace(',');
  color.a = readFloat(string);
  
  string.expectAfterWhitespace(']');
  
  return color;
}
