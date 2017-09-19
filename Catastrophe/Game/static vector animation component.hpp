//
//  static vector animation component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 17/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef static_vector_animation_component_hpp
#define static_vector_animation_component_hpp

#include "vector sprite.hpp"
#include "animation component.hpp"

class StaticVectorAnimationComponent final : public AnimationComponent {
public:
  StaticVectorAnimationComponent(Entity *, const Sprite &, glm::vec2);
  
  void update(RenderingState &, const PhysicsState &, float) override;

private:
  Sprite sprite;
  glm::vec2 scale;
};

#endif
