//
//  static animation component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 17/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef static_animation_component_hpp
#define static_animation_component_hpp

#include "transform.hpp"
#include <yaml-cpp/node/node.h>
#include "animation component.hpp"

class StaticAnimationComponent final : public AnimationComponent {
public:
  StaticAnimationComponent(Entity *, Sprite &&, Transform, const YAML::Node &);
  
  void update(float) override;
  const DrawCommands &getDrawCommands() const override;
  const Frame &getFrame() const override;
  glm::mat3 getModelMat() const override;

private:
  Sprite sprite;
  Frame frame;
  Transform transform;
  glm::mat3 model;
};

#endif
