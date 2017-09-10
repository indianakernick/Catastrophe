//
//  player physics state.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef player_physics_state_hpp
#define player_physics_state_hpp

#include "physics state.hpp"
#include "../Libraries/Box2D/Common/b2Math.h"

class PlayerPhysicsState final : public PhysicsState {
public:
  b2Vec2 vel = {0.0f, 0.0f};
  bool onGround = false;
};

#endif
