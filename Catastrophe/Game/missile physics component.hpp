//
//  missile physics component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef missile_physics_component_hpp
#define missile_physics_component_hpp

#include "body physics component.hpp"

class MissilePhysicsComponent final : public BodyPhysicsComponent {
public:
  MissilePhysicsComponent() = default;
  
  void init(b2World &, const YAML::Node &) override;
  void preStep(float) override;
  void postStep() override;
  
  void beginContact();

private:
  static constexpr float TOP_SPEED = 20.0f;

  float moveForce = 10.0f;
  float turnTorque = 1.0f;
  bool contacted = false;
};

#endif
