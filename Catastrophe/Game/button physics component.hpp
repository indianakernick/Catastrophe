//
//  button physics component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 5/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef button_physics_component_hpp
#define button_physics_component_hpp

#include "physics component.hpp"

class ButtonPhysicsComponent final : public PhysicsComponent {
public:
  ButtonPhysicsComponent() = default;
  
  void init(b2World &, const YAML::Node &) override;
  void preStep(float) override;
  void postStep() override;
  
  void beginContactingPlayer();
  void endContactingPlayer();
  
  bool playerOnButton() const;

private:
  bool contacting = false;
};

#endif
