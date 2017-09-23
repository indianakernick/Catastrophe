//
//  vector circle shape.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 5/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "vector circle shape.hpp"

#include "nvg helper.hpp"
#include "yaml helper.hpp"

void ShapeCircle::load(const YAML::Node &node, const FrameSize frameSize) {
  Shape::load(node, frameSize);
  points = readIndicies(getChild(node, "points"), frameSize.numPoints);
  
  if (const YAML::Node &radiusNode = node["radius"]) {
    radius = readIndex(radiusNode, frameSize.numScalars);
  }
}

void ShapeCircle::draw(NVGcontext *context, const Frame &frame) const {
  for (auto i = points.cbegin(); i != points.cend(); ++i) {
    preDraw(context, frame);
    
    const Coord circleRadius = radius == NULL_INDEX ? 1.0f : frame.scalars[radius];
    const Point center = frame.points[points[*i]];
    nvgCircle(context, center.x, center.y, circleRadius);
    
    postDraw(context, frame);
  }
}
