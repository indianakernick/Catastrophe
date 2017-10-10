//
//  oscillating physics component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 23/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef oscillating_physics_component_hpp
#define oscillating_physics_component_hpp

#include "physics component.hpp"
#include "../Libraries/Box2D/Common/b2Math.h"

class OscillatingPhysicsComponent final : public PhysicsComponent {
public:
  OscillatingPhysicsComponent() = default;
  
  void init(b2World &, const YAML::Node &) override;
  void preStep(float) override;
  void postStep() override;
  
private:
  b2Vec2 first;
  b2Vec2 second;
  b2Vec2 toSecond;
};

#endif
