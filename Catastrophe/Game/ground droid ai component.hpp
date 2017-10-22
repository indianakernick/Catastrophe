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
  enum class MoveSpeed {
    STOP,
    SLOW,
    FAST
  };
  enum class MoveDir {
    LEFT,
    RIGHT
  };

  GroundDroidAIComponent() = default;
  
  virtual MoveDir getMoveDir() const = 0;
  virtual MoveSpeed getMoveSpeed() const = 0;
  virtual float getGunAngle() const;
  virtual bool shouldShoot() const;
};

#endif
