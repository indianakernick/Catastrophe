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
  const Index index = string.parseNumber<Index>();
  if (index >= size) {
    throw DrawCommandError("Index out of range");
  }
  return index;
}

bool isLiteral(Utils::ParseString &string) {
  return string.front() == '[';
}

glm::vec2 readPoint(Utils::ParseString &string) {
  glm::vec2 point;
  
  string.expectAfterWhitespace('[');
  string.parseNumber(point.x);
  
  string.expectAfterWhitespace(',');
  string.parseNumber(point.y);
  
  string.expectAfterWhitespace(']');
  
  return point;
}

float readScalar(Utils::ParseString &string) {
  float scalar;
  
  string.expectAfterWhitespace('[');
  string.parseNumber(scalar);
  
  string.expectAfterWhitespace(']');
  
  return scalar;
}

glm::vec4 readColor(Utils::ParseString &string) {
  glm::vec4 color;
  
  string.expectAfterWhitespace('[');
  string.parseNumber(color.r);
  
  string.expectAfterWhitespace(',');
  string.parseNumber(color.g);
  
  string.expectAfterWhitespace(',');
  string.parseNumber(color.b);
  
  string.expectAfterWhitespace(',');
  string.parseNumber(color.a);
  
  string.expectAfterWhitespace(']');
  
  return color;
}
