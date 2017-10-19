//
//  systems fwd.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 19/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef systems_fwd_hpp
#define systems_fwd_hpp

#include "component names.hpp"

#define COMPONENT(NAME) class NAME##System;
#define LAST_COMPONENT(NAME) COMPONENT(NAME)
COMPONENTS
#undef LAST_COMPONENT
#undef COMPONENT

#endif
