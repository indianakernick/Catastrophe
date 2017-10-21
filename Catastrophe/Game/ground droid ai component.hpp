//
//  ground droid ai component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 22/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef ground_droid_ai_component_hpp
#define ground_droid_ai_component_hpp

#include "ai component.hpp"

class GroundDroidAIComponent : public AIComponent {
public:
  GroundDroidAIComponent() = default;
  
  virtual bool shouldMoveLeft() const = 0;
  virtual bool shouldMoveRight() const = 0;
  virtual bool shouldMoveFast() const = 0;
  virtual bool shouldShoot() const;
};

#endif
