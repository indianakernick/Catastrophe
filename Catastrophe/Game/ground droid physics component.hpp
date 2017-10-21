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
  
  void init(b2World &, const YAML::Node &) override;
  void preStep(float) override;
  void postStep() override;
  
  float getVelX() const;
  bool canSeePlayer() const;
  glm::vec2 getPlayerPos() const;

private:
  float moveForce = 100.0f;
  float maxMoveSpeed = 10.0f;
  glm::vec2 playerPos;
  bool seePlayer = false;
  
  void applyMoveForce(float);
};

#endif
