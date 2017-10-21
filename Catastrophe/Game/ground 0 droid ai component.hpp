//
//  ground 0 droid ai component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef ground_0_droid_ai_component_hpp
#define ground_0_droid_ai_component_hpp

#include "ground droid ai component.hpp"

class Ground0DroidAIComponent final : public GroundDroidAIComponent {
public:
  Ground0DroidAIComponent() = default;
  
  void init(const YAML::Node &) override;
  void update(float) override;
  
  bool shouldMoveLeft() const override;
  bool shouldMoveRight() const override;
  bool shouldMoveFast() const override;

private:
  //The x coordinate of the first patrol point
  float patrolFirst = 0.0f;
  //The x coordinate of the second patrol point
  float patrolSecond = 1.0f;
  //The maximum distance from the patrol point the droid will chase
  //the player
  float maxDistFromPatrol = 2.0f;
  bool moveRight = false;
  bool toSecond = true;
  bool chasing = false;
  
  void patrol(float);
  void chase(float, float);
};

#endif
