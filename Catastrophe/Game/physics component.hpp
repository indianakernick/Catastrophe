//
//  physics component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef physics_component_hpp
#define physics_component_hpp

#include "../Libraries/Box2D/Dynamics/b2Body.h"

class PhysicsComponent {
public:
  PhysicsComponent() = default;
  ~PhysicsComponent() = default;
  
  b2Body *body = nullptr;
};

#endif
