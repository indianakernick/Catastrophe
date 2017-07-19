//
//  entity id.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef entity_id_hpp
#define entity_id_hpp

#include <limits>
#include <cstdint>

using EntityID = uint32_t;
constexpr EntityID NULL_ENTITY = std::numeric_limits<EntityID>::max();

#endif
