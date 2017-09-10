//
//  physics state.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef physics_state_hpp
#define physics_state_hpp

#include "../Libraries/Box2D/Common/b2Math.h"

class PhysicsState {
public:
  PhysicsState() = default;
  virtual ~PhysicsState() = default;
  
  b2Vec2 pos = {0.0f, 0.0f};
};

#endif
