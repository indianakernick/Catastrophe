//
//  invisible animation component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 4/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef invisible_animation_component_hpp
#define invisible_animation_component_hpp

#include <yaml-cpp/node/node.h>
#include "animation component.hpp"

class InvisibleAnimationComponent final : public AnimationComponent {
public:
  InvisibleAnimationComponent(const YAML::Node &, const YAML::Node &);
  
  void update(float) override;
  const Sprite &getSprite() const override;
  const Frame &getFrame() const override;
  glm::mat3 getModelMat() const override;

private:
  static const Sprite sprite;
  static const Frame frame;
};

#endif
