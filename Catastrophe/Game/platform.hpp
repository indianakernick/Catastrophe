//
//  platform.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 29/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef platform_hpp
#define platform_hpp

#include "rect.hpp"
#include "factory fwd.hpp"

std::unique_ptr<Entity> makePlatform(
  EntityID,
  Systems,
  Rect
);

#endif
