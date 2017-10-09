//
//  launcher animation component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 5/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef launcher_animation_component_hpp
#define launcher_animation_component_hpp

#include <yaml-cpp/node/node.h>
#include "animation component.hpp"

class LauncherAnimationComponent final : public AnimationComponent {
public:
  LauncherAnimationComponent(const YAML::Node &, const YAML::Node &);

  void update(float) override;
  float getProgress() const override;
  glm::mat3 getModelMat() const override;

private:
  glm::mat3 model;
  float progress = 0.0f;
};

#endif
