//
//  object types.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 5/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef object_types_hpp
#define object_types_hpp

#include <Simpleton/Utils/type name.hpp>
#include <Simpleton/Utils/instance limiter.hpp>

template <typename Symbol>
void *getUserData() {
  return reinterpret_cast<void *>(Utils::typeHash<Symbol>());
}

namespace Symbol {
  MAKE_SYMBOL(PlayerBody);
  MAKE_SYMBOL(PlayerFoot);
  MAKE_SYMBOL(Platform);
};

#endif
