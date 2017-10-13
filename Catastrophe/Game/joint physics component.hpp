//
//  joint physics component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 4/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef joint_physics_component_hpp
#define joint_physics_component_hpp

#include "physics component.hpp"

class b2Joint;

class JointPhysicsComponent : public PhysicsComponent {
public:
  JointPhysicsComponent() = default;
  
  void init(b2World &, const YAML::Node &) override;
  void quit(b2World &) override;
  void preStep(float) override {}
  void postStep() override {}
  AABB getAABB() const override final;

  b2Joint *getJoint();
  const b2Joint *getJoint() const;
  
protected:
  b2Joint *joint = nullptr;
};

#endif
