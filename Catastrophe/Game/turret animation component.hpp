//
//  turret animation component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 14/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef turret_animation_component_hpp
#define turret_animation_component_hpp

#include "transform.hpp"
#include "animation component.hpp"

class TurretAnimationComponent final : public AnimationComponent {
public:
  TurretAnimationComponent() = default;
  
  void init(const YAML::Node &) override;
  void update(float) override;
  float getProgress() const override;
  glm::mat3 getModelMat() const override;

private:
  Transform transform;
  glm::mat3 model;
};

#endif
