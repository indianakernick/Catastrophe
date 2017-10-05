//
//  proximity sensor physics component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 5/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef proximity_sensor_physics_component_hpp
#define proximity_sensor_physics_component_hpp

#include <yaml-cpp/node/node.h>
#include "physics component.hpp"

class ProximitySensorPhysicsComponent final : public PhysicsComponent {
public:
  ProximitySensorPhysicsComponent(const YAML::Node &, const YAML::Node &);
  
  void preStep(float) override;
  void postStep() override;
  
  void beginContactingPlayer();
  void endContactingPlayer();
  
  bool playerIsClose() const;

private:
  bool contacting = false;
};

#endif
