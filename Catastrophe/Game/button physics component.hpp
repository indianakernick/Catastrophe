//
//  button physics component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 5/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef button_physics_component_hpp
#define button_physics_component_hpp

#include "body physics component.hpp"

class ButtonPhysicsComponent final : public BodyPhysicsComponent {
public:
  ButtonPhysicsComponent() = default;
  
  void beginContactingPlayer();
  void endContactingPlayer();
  
  bool playerOnButton() const;

private:
  bool contacting = false;
};

#endif
