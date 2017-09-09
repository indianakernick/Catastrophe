//
//  vector line shape.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 5/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef vector_line_shape_hpp
#define vector_line_shape_hpp

#include "vector sprite.hpp"

class ShapeLine final : public Shape {
public:
  void load(const YAML::Node &, FrameSize) override;
  void draw(NVGcontext *, const Frame &) const override;

private:
  Indicies points;
  NVGlineCap cap = NVG_BUTT;
  NVGlineCap join = NVG_MITER;
  Index strokeColor = NULL_INDEX;
  Index fillColor = NULL_INDEX;
  Index strokeWidth = NULL_INDEX;
};

#endif