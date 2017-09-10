//
//  rendering state.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef rendering_state_hpp
#define rendering_state_hpp

#include <glm/mat3x3.hpp>

class RenderingState {
public:
  RenderingState() = default;
  virtual ~RenderingState() = default;
  
  glm::mat3 modelMat;
};

#endif
