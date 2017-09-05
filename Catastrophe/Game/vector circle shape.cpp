//
//  vector circle shape.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 5/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "vector circle shape.hpp"

#include "nvg helper.hpp"
#include "vector file helper.hpp"

void ShapeLine::load(const YAML::Node &node, const FrameSize) {
  //@TODO use frameSize to check bounds of indicies
  
  points = getChild(node, "points").as<Indicies>();
  
  if (const YAML::Node &radiusNode = node["radius"]) {
    radius = radiusNode.as<Index>();
  }
  if (const YAML::Node &strokeColorNode = node["stroke color"]) {
    strokeColor = strokeColorNode.as<Index>();
  }
  if (const YAML::Node &fillColorNode = node["fill color"]) {
    fillColor = fillColorNode.as<Index>();
  }
  if (const YAML::Node &strokeWidthNode = node["stroke width"]) {
    strokeWidth = strokeWidthNode.as<Index>();
  }
}

void ShapeLine::draw(NVGcontext *context, const Frame &frame) const {
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
