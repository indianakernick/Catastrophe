//
//  player physics component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 3/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef player_physics_component_hpp
#define player_physics_component_hpp

#include "physics component.hpp"

class b2Fixture;

class PlayerPhysicsComponent final : public PhysicsComponent {
public:
  explicit PlayerPhysicsComponent(b2Body *);
  
  b2Vec2 getPos() const override;
  
  b2Body *getBody() override;
  const b2Body *getBody() const override;

  bool onGround() const;
  
  void beginContactingGround();
  void endContactingGround();

private:
  b2Body *body;
  int footContactCount = 0;
};

#endif
