//
//  droid bullet physics component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 22/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef droid_bullet_physics_component_hpp
#define droid_bullet_physics_component_hpp

#include "body physics component.hpp"

class DroidBulletPhysicsComponent final : public BodyPhysicsComponent {
public:
  DroidBulletPhysicsComponent() = default;
  
  void init(b2World &, const YAML::Node &) override;
  void postStep() override;
  
  void beginContact();

private:
  bool contacted = false;
};

#endif
