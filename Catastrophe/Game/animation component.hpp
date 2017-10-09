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
#include <glm/mat3x3.hpp>

class AnimationComponent : public Component {
public:
  AnimationComponent() = default;
  virtual ~AnimationComponent() = default;
  
  virtual void update(float) = 0;
  virtual float getProgress() const = 0;
  virtual glm::mat3 getModelMat() const = 0;
};

#endif
