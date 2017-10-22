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
#include <Simpleton/Utils/type list.hpp>
#include <Simpleton/Utils/instance limiter.hpp>

template <typename Symbol>
void *getUserData() {
  return reinterpret_cast<void *>(Utils::typeHash<Symbol>());
}

template <typename Symbol0, typename Symbol1>
constexpr bool symbolLess() {
  //don't change this to Utils::typeLess
  return Utils::typeHash<Symbol0>() < Utils::typeHash<Symbol1>();
}

template <typename Symbol0, typename Symbol1>
std::pair<void *, void *> getUserData() {
  if constexpr (symbolLess<Symbol0, Symbol1>()) {
    return {getUserData<Symbol0>(), getUserData<Symbol1>()};
  } else {
    return {getUserData<Symbol1>(), getUserData<Symbol0>()};
  }
}

#define SYMBOLS                                                                 \
  SYMBOL(PlayerBody)                                                            \
  SYMBOL(PlayerFoot)                                                            \
  SYMBOL(Platform)                                                              \
  SYMBOL(Pentagon)                                                              \
  SYMBOL(Deadly)                                                                \
  SYMBOL(Missile)                                                               \
  SYMBOL(GroundDroidFoot)                                                       \
  SYMBOL(GroundDroidBody)                                                       \
  SYMBOL(DroidBullet)                                                           \
  LAST_SYMBOL(TouchSensor)

namespace Symbol {
  #define SYMBOL(NAME) MAKE_SYMBOL(NAME);
  #define LAST_SYMBOL(NAME) SYMBOL(NAME)
  SYMBOLS
  #undef LAST_SYMBOL
  #undef SYMBOL
};

using Symbols = Utils::TypeList<
  #define SYMBOL(NAME) Symbol::NAME,
  #define LAST_SYMBOL(NAME) Symbol::NAME
  SYMBOLS
  #undef LAST_SYMBOL
  #undef SYMBOL
>;

#undef SYMBOLS

inline void *getUserData(const std::string &symbolName) {
  try {
    return Utils::getValueByName<void *, Symbols>("Symbol::" + symbolName, [] (auto t) {
      return getUserData<typename decltype(t)::type>();
    });
  } catch (Utils::TypeNotFound &) {
    throw std::runtime_error("Invalid symbol name");
  }
}

#endif
