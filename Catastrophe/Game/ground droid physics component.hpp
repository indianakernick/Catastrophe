//
//  ground droid physics component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef ground_droid_physics_component_hpp
#define ground_droid_physics_component_hpp

#include "body physics component.hpp"

class GroundDroidPhysicsComponent final : public BodyPhysicsComponent {
public:
  GroundDroidPhysicsComponent() = default;
  
  float getVelX() const;
};

#endif
