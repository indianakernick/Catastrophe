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
class b2Joint;
class b2World;

class PhysicsComponent : public Component {
public:
  PhysicsComponent() = default;
  virtual ~PhysicsComponent() = default;
  
  //Called before b2World::Step
  virtual void preStep(float) = 0;
  //Called after b2World::Step
  virtual void postStep() = 0;
  
  glm::vec2 getPos() const;
  float getAngle() const;
  
  b2Body *body = nullptr;
  b2Joint *joint = nullptr;
};

#endif
