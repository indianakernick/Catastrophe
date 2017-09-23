//
//  vector circle shape.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 5/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef vector_circle_shape_hpp
#define vector_circle_shape_hpp

#include "vector sprite.hpp"

class ShapeCircle final : public Shape {
public:
  void load(const YAML::Node &, FrameSize) override;
  void draw(NVGcontext *, const Frame &) const override;

private:
  Indicies points;
  Index radius = NULL_INDEX;
};

#endif
