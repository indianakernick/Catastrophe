//
//  ground 1 droid ai component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 22/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef ground_1_droid_ai_component_hpp
#define ground_1_droid_ai_component_hpp

#include <glm/vec2.hpp>
#include "ground droid ai component.hpp"

class Ground1DroidAIComponent final : public GroundDroidAIComponent {
public:
  Ground1DroidAIComponent() = default;
  
  void init(const YAML::Node &) override;
  void update(float) override;
  
  MoveDir getMoveDir() const override;
  MoveSpeed getMoveSpeed() const override;
  float getGunAngle() const override;
  bool shouldShoot() const override;

private:
  float lookingDuration = 1.0f;
  float timeSinceLook = 0.0f;
  float gunRotateSpeed = 1.0f;
  float gunAngle = 0.0f;
  bool lookingRight = true;
  bool chasing = false;
  
  void chase(glm::vec2, glm::vec2, bool);
  void stand(float, bool);
};

#endif
