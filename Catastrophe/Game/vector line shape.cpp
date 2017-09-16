//
//  vector line shape.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 5/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "vector line shape.hpp"

#include "nvg helper.hpp"
#include "yaml helper.hpp"

namespace {
  class BadLineCap {};

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
      throw BadLineCap();
    }
  }
}

void ShapeLine::load(const YAML::Node &node, const FrameSize frameSize) {
  points = readIndicies(getChild(node, "points"), frameSize.numPoints);
  
  if (const YAML::Node &capNode = node["cap"]) {
    try {
      cap = readCap(capNode.as<std::string>());
    } catch (BadLineCap &) {
      throw std::runtime_error(
        "Invalid cap at line "
        + std::to_string(capNode.Mark().line)
      );
    }
  }
  if (const YAML::Node &joinNode = node["join"]) {
    try {
      join = readCap(joinNode.as<std::string>());
    } catch (BadLineCap &) {
      throw std::runtime_error(
        "Invalid join at line "
        + std::to_string(joinNode.Mark().line)
      );
    }
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
