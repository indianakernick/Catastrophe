//
//  systems.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef systems_hpp
#define systems_hpp

#include "ai system.hpp"
#include "input system.hpp"
#include "spawn system.hpp"
#include "physics system.hpp"
#include "component names.hpp"
#include "particle system.hpp"
#include "tracking system.hpp"
#include "animation system.hpp"
#include "rendering system.hpp"

#define COMPONENT(NAME, ID_NAME) static NAME##System *ID_NAME;
#define LAST_COMPONENT(NAME, ID_NAME) COMPONENT(NAME, ID_NAME)
struct Systems {
  COMPONENTS
};
#undef LAST_COMPONENT
#undef COMPONENT

#endif
