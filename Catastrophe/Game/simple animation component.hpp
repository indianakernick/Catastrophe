//
//  simple animation component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef simple_animation_component_hpp
#define simple_animation_component_hpp

#include "animation component.hpp"

class SimpleAnimationComponent final : public AnimationComponent {
public:
  SimpleAnimationComponent() = default;
  
  void update(RenderingState &, const PhysicsState &, float) override;
};

#endif
