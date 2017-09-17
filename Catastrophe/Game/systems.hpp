//
//  systems.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 17/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef systems_hpp
#define systems_hpp

#include "input system.hpp"
#include "physics system.hpp"
#include "animation system.hpp"
#include "rendering system.hpp"

struct Systems {
  InputSystem &input;
  PhysicsSystem &physics;
  AnimationSystem &animation;
  RenderingSystem &rendering;
};

#endif
