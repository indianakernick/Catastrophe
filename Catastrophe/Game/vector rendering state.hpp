//
//  vector rendering state.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 10/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef vector_rendering_state_hpp
#define vector_rendering_state_hpp

#include "vector sprite.hpp"
#include "rendering state.hpp"

class VectorRenderingState final : public RenderingState {
public:
  Shapes shapes;
  Frame frame;
};

#endif
