//
//  command literals.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef command_literals_hpp
#define command_literals_hpp

#include "vector sprite.hpp"
#include "animation data types.hpp"
#include <Simpleton/Utils/parse string.hpp>

Index readIndex(Utils::ParseString &, Index);
bool isLiteral(Utils::ParseString &);
glm::vec2 readPoint(Utils::ParseString &);
float readScalar(Utils::ParseString &);
glm::vec4 readColor(Utils::ParseString &);

template <typename Type>
auto readLiteral(Utils::ParseString &string) {
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
