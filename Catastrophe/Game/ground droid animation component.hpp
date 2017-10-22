//
//  ground droid animation component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 21/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef ground_droid_animation_component_hpp
#define ground_droid_animation_component_hpp

#include "transform.hpp"
#include "velocity direction.hpp"
#include "animation component.hpp"

class GroundDroidAnimationComponent final : public AnimationComponent {
public:
  GroundDroidAnimationComponent() = default;
 
  void init(const YAML::Node &) override;
  void update(float) override;
  float getProgress() const override;
  glm::mat3 getModelMat() const override;
  
  float getDir() const;

private:
  Transform transform;
  glm::mat3 mat;
  float progress = 0.0f;
  float bopSpeed = 1.0f;
  float dir = 1.0f;
};

#endif
