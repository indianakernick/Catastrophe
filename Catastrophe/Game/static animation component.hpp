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
#include "animation component.hpp"

class StaticAnimationComponent final : public AnimationComponent {
public:
  StaticAnimationComponent(Entity *, const Sprite &, Transform);
  
  void update(float) override;
  const Shapes &getShapes() const override;
  const Frame &getFrame() const override;
  glm::mat3 getModelMat() const override;

private:
  Sprite sprite;
  Frame frame;
  Transform transform;
  glm::mat3 model;
};

#endif
