//
//  vector line shape.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 5/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "vector line shape.hpp"

#include "nvg helper.hpp"
#include "vector file helper.hpp"

namespace {
  NVGlineCap readCap(const std::string &str) {
           if (str == "butt") {
      return NVG_BUTT;
    } else if (str == "round") {
      return NVG_ROUND;
    } else if (str == "square") {
      return NVG_SQUARE;
    } else if (str == "bevel") {
      return NVG_BEVEL;
    } else if (str == "miter") {
      return NVG_MITER;
    } else {
      throw std::runtime_error("Invalid line cap");
    }
  }
}

void ShapeLine::load(const YAML::Node &node, const FrameSize) {
  //@TODO use frameSize to check bounds of indicies
  
  points = getChild(node, "points").as<Indicies>();
  
  if (const YAML::Node &capNode = node["cap"]) {
    cap = readCap(capNode.as<std::string>());
  }
  if (const YAML::Node &capNode = node["join"]) {
    join = readCap(capNode.as<std::string>());
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
  
  nvgLineCap(context, cap);
  nvgLineJoin(context, join);

  const Point firstPoint = frame.points[points.front()];
  nvgMoveTo(context, firstPoint.x, firstPoint.y);
  for (auto i = points.cbegin() + 1; i != points.cend(); ++i) {
    const Point point = frame.points[*i];
    nvgLineTo(context, point.x, point.y);
  }
  
  if (fillColor != NULL_INDEX) {
    nvgFill(context);
  }
  if (strokeColor != NULL_INDEX) {
    nvgStroke(context);
  }
}
