//
//  systems registry.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 5/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef systems_registry_hpp
#define systems_registry_hpp

#include "input system.hpp"
#include "physics system.hpp"
#include "entity manager.hpp"
#include "animation system.hpp"
#include "rendering system.hpp"
#include "rendering context.hpp"

struct Systems {
  static InputSystem *input;
  static PhysicsSystem *physics;
  static AnimationSystem *animation;
  static RenderingSystem *rendering;
  static EntityManager *entities;
  static RenderingContext *renderer;
};

#endif
