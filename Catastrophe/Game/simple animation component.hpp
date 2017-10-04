//
//  simple animation component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 17/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef simple_animation_component_hpp
#define simple_animation_component_hpp

#include "transform.hpp"
#include <yaml-cpp/node/node.h>
#include "animation component.hpp"
#include <Simpleton/Time/simple anim.hpp>

class SimpleAnimationComponent final : public AnimationComponent {
public:
  SimpleAnimationComponent(const YAML::Node &, const YAML::Node &, RenderingContext &);
  
  void update(float) override;
  const Sprite &getSprite() const override;
  const Frame &getFrame() const override;
  glm::mat3 getModelMat() const override;

private:
  Sprite sprite;
  Frame frame;
  Transform transform;
  glm::mat3 model;
  Time::SimpleAnim<float> anim;
};

#endif
