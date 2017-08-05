//
//  physics component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef physics_component_hpp
#define physics_component_hpp

class b2Body;
struct b2Vec2;

class PhysicsComponent {
public:
  PhysicsComponent() = default;
  virtual ~PhysicsComponent() = default;
  
  virtual b2Vec2 getPos() const = 0;
  
  virtual b2Body *getBody() = 0;
  virtual const b2Body *getBody() const = 0;
};

#endif
