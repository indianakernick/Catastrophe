//
//  animation component.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef animation_component_hpp
#define animation_component_hpp

class PhysicsState;
class RenderingState;

class AnimationComponent {
public:
  AnimationComponent() = default;
  virtual ~AnimationComponent() = default;
  
  virtual void update(RenderingState &, const PhysicsState &, float) = 0;
};

#endif
