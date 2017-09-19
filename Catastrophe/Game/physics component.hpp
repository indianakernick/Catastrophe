//
//  physics component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef physics_component_hpp
#define physics_component_hpp

#include <glm/vec2.hpp>
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
  virtual void preStep(float) = 0;
  //Called after b2World::Step
  virtual void postStep() = 0;
  
  glm::vec2 getPos() const;
  
  b2Body *body = nullptr;
};

#endif
