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
#include "vector sprite.hpp"

class AnimationComponent : public Component {
public:
  explicit AnimationComponent(Entity *);
  virtual ~AnimationComponent() = default;
  
  virtual void update(float) = 0;
  virtual const Shapes &getShapes() const = 0;
  virtual const Frame &getFrame() const = 0;
  virtual glm::mat3 getModelMat() const = 0;
};

#endif
