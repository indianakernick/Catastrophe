//
//  turret physics component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 14/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef turret_physics_component_hpp
#define turret_physics_component_hpp

#include "physics component.hpp"

class TurretPhysicsComponent final : public PhysicsComponent {
public:
  TurretPhysicsComponent() = default;
  
  void init(b2World &, const YAML::Node &) override;
  void quit(b2World &) override {};
  void preStep(float) override;
  void postStep() override {};
  AABB getAABB() const override;

  glm::vec2 getPos() const;
  float getAngle() const;

private:
  glm::vec2 pos;
  float angle;
  float minAngle;
  float maxAngle;
};

#endif
