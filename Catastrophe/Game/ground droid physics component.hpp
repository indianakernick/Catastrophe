//
//  ground droid physics component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef ground_droid_physics_component_hpp
#define ground_droid_physics_component_hpp

#include "ground contact.hpp"
#include "body physics component.hpp"
#include "../Libraries/Box2D/Common/b2Math.h"

class GroundDroidPhysicsComponent final : public BodyPhysicsComponent {
public:
  GroundDroidPhysicsComponent() = default;
  
  void init(b2World &, const YAML::Node &) override;
  void preStep(float) override;
  void postStep() override;
  
  bool canSeePlayer() const;
  glm::vec2 getPlayerPos() const;
  glm::vec2 getRelVel() const;
  bool onGround() const;
  
  void beginContactingGround(b2Body *);
  void endContactingGround(b2Body *);

private:
  GroundContact groundContact;
  b2Vec2 playerPos;
  float moveForce = 100.0f;
  float slowMoveSpeed = 2.0f;
  float fastMoveSpeed = 3.0f;
  float maxViewDistance = 4.0f;
  bool seePlayer = false;
  bool fast = false;
  
  void applyMoveForce(float);
  auto getPlayer() const;
  void lookForPlayer();
  void limitSpeed();
};

#endif