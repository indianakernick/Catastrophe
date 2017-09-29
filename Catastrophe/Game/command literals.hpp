//
//  command literals.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef command_literals_hpp
#define command_literals_hpp

#include "parse string.hpp"
#include "vector sprite.hpp"
#include "animation data types.hpp"

Index readIndex(ParseString &, Index);
bool isLiteral(ParseString &);
glm::vec2 readPoint(ParseString &);
float readScalar(ParseString &);
glm::vec4 readColor(ParseString &);

template <typename Type>
auto readLiteral(ParseString &string) {
  if constexpr (std::is_same<Type, PointType>::value) {
    return readPoint(string);
  } else if constexpr (std::is_same<Type, ScalarType>::value) {
    return readScalar(string);
  } else if constexpr (std::is_same<Type, ColorType>::value) {
    return readColor(string);
  } else {
    assert(false);
    return 0;
  }
}

#endif
