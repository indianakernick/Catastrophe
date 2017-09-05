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
#include <nanovg/nanovg.h>

class ShapeLine final : public Shape {
public:
  void load(const YAML::Node &, FrameSize) override;
  void draw(NVGcontext *, const Frame &) const override;

private:
  Indicies points;
  Index radius = NULL_INDEX;
  Index strokeColor = NULL_INDEX;
  Index fillColor = NULL_INDEX;
  Index strokeWidth = NULL_INDEX;
};

#endif
