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
  PlayerPhysicsComponent(Entity *, b2Body *);
  
  void preStep(float) override;
  void postStep() override;
  
  void beginContactingGround();
  void endContactingGround();
  
  glm::vec2 getVel() const;
  bool onGround() const;

private:
  int footContactCount = 0;
  float timeTillFinishJump = 0.0f;

  void applyMoveForce(float);
  void moveLeft();
  void moveRight();
  void jump(float);
};

#endif
