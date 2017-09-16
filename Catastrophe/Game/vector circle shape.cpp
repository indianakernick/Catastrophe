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
  points = readIndicies(getChild(node, "points"), frameSize.numPoints);
  
  if (const YAML::Node &radiusNode = node["radius"]) {
    radius = readIndex(radiusNode, frameSize.numScalars);
  }
  if (const YAML::Node &strokeColorNode = node["stroke color"]) {
    strokeColor = readIndex(strokeColorNode, frameSize.numColors);
  }
  if (const YAML::Node &fillColorNode = node["fill color"]) {
    fillColor = readIndex(fillColorNode, frameSize.numColors);
  }
  if (const YAML::Node &strokeWidthNode = node["stroke width"]) {
    strokeWidth = readIndex(strokeWidthNode, frameSize.numScalars);
  }
}

void ShapeCircle::draw(NVGcontext *context, const Frame &frame) const {
  for (auto i = points.cbegin(); i != points.cend(); ++i) {
    nvgBeginPath(context);
    
    if (strokeColor != NULL_INDEX) {
      nvgStrokeColor(context, frame.colors[strokeColor]);
    }

    if (fillColor != NULL_INDEX) {
      nvgFillColor(context, frame.colors[fillColor]);
    }

    if (strokeWidth != NULL_INDEX) {
      nvgStrokeWidth(context, frame.scalars[strokeWidth]);
    } else if (strokeColor != NULL_INDEX) {
      nvgStrokeWidth(context, 1.0f);
    }
    
    const Coord circleRadius = radius == NULL_INDEX ? 1.0f : frame.scalars[radius];
    const Point center = frame.points[points[*i]];
    nvgCircle(context, center.x, center.y, circleRadius);
    
    if (fillColor != NULL_INDEX) {
      nvgFill(context);
    }
    if (strokeColor != NULL_INDEX) {
      nvgStroke(context);
    }
  }
}
