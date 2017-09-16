//
//  object types.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 5/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef object_types_hpp
#define object_types_hpp

#include <utility>
#include <Simpleton/Utils/type name.hpp>
#include <Simpleton/Utils/instance limiter.hpp>

template <typename Symbol>
void *getUserData() {
  return reinterpret_cast<void *>(Utils::typeHash<Symbol>());
}

template <typename Symbol0, typename Symbol1>
constexpr bool symbolLess() {
  return Utils::typeLess<Symbol0, Symbol1>();
}

template <typename Symbol0, typename Symbol1>
std::pair<void *, void *> getUserData() {
  if constexpr (symbolLess<Symbol0, Symbol1>()) {
    return {getUserData<Symbol0>(), getUserData<Symbol1>()};
  } else {
    return {getUserData<Symbol1>(), getUserData<Symbol0>()};
  }
}

namespace Symbol {
  MAKE_SYMBOL(PlayerBody);
  MAKE_SYMBOL(PlayerFoot);
  MAKE_SYMBOL(Platform);
};

#endif
