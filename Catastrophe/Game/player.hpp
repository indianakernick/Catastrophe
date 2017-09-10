//
//  player.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include "factory fwd.hpp"
#include "../Libraries/Box2D/Common/b2Math.h"

std::unique_ptr<Entity> makePlayer(
  EntityID,
  InputSystem &,
  PhysicsSystem &,
  AnimationSystem &,
  RenderingSystem &,
  b2Vec2
);

#endif
