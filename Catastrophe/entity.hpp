//
//  entity.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 18/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef entity_hpp
#define entity_hpp

#include "settings.hpp"

template <typename Settings>
class Entity {
public:
  static_assert(IsSettings<Settings>::value);
  
  using Bitset = typename Settings::Bitset;
  
  Entity() = default;
  ~Entity() = default;
  
  Bitset bitset = 0;
  size_t compIndex;
  bool alive = false;
};

#endif
