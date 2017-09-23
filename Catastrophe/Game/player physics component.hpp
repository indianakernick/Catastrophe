//
//  player physics component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 3/8/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef player_physics_component_hpp
#define player_physics_component_hpp

#include <forward_list>
#include <yaml-cpp/node/node.h>
#include "physics component.hpp"

class PlayerPhysicsComponent final : public PhysicsComponent {
public:
  PlayerPhysicsComponent(Entity *, b2Body *, const YAML::Node &);
  
  void preStep(float) override;
  void postStep() override;
  
  void beginContactingGround(b2Body *);
  void endContactingGround(b2Body *);
  
  glm::vec2 getRelVel() const;
  bool onGround() const;

private:
  std::forward_list<b2Body *> groundBodies;
  float timeTillFinishJump = 0.0f;

  void applyMoveForce(float);
  void jump(float);
};

#endif
