//
//  physics component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef physics_component_hpp
#define physics_component_hpp

#include "component.hpp"

class b2Body;
struct b2Vec2;
class PhysicsState;
class InputCommands;

class PhysicsComponent : public Component {
public:
  PhysicsComponent(Entity *, b2Body *);
  virtual ~PhysicsComponent() = default;
  
  //Called before b2World::Step
  virtual void preStep(PhysicsState &, const InputCommands &, float) = 0;
  //Called after b2World::Step
  virtual void postStep(PhysicsState &, const InputCommands &) = 0;
  
  b2Body *body = nullptr;
};

#endif
