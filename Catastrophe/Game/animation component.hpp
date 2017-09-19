//
//  animation component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef animation_component_hpp
#define animation_component_hpp

#include "component.hpp"

class PhysicsState;
class RenderingState;

class AnimationComponent : public Component {
public:
  explicit AnimationComponent(Entity *);
  virtual ~AnimationComponent() = default;
  
  virtual void update(float) = 0;
};

#endif
