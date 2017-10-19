//
//  systems.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "systems.hpp"

#define COMPONENT(NAME, ID_NAME) NAME##System *Systems::ID_NAME = nullptr;
#define LAST_COMPONENT(NAME, ID_NAME) COMPONENT(NAME, ID_NAME)
COMPONENTS
#undef LAST_COMPONENT
#undef COMPONENT
