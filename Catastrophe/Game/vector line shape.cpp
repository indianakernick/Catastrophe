//
//  vector line shape.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 5/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "vector line shape.hpp"

#include "yaml helper.hpp"

void ShapeLine::load(const YAML::Node &node, const FrameSize frameSize) {
  Shape::load(node, frameSize);
  points = readIndicies(getChild(node, "points"), frameSize.numPoints);
}

void ShapeLine::draw(NVGcontext *context, const Frame &frame) const {
  preDraw(context, frame);

  const Point firstPoint = frame.points[points.front()];
  nvgMoveTo(context, firstPoint.x, firstPoint.y);
  for (auto i = points.cbegin() + 1; i != points.cend(); ++i) {
    const Point point = frame.points[*i];
    nvgLineTo(context, point.x, point.y);
  }
  
  postDraw(context, frame);
}
