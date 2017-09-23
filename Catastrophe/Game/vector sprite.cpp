//
//  vector sprite.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 2/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "vector sprite.hpp"

#include "yaml helper.hpp"

namespace {
  NVGlineCap readCap(const YAML::Node &capNode) {
    const std::string capStr = capNode.as<std::string>();
    if (capStr == "butt") {
      return NVG_BUTT;
    } else if (capStr == "round") {
      return NVG_ROUND;
    } else if (capStr == "square") {
      return NVG_SQUARE;
    } else {
      throw std::runtime_error(
        "Invalid stroke cap at line "
        + std::to_string(capNode.Mark().line)
      );
    }
  }
  
  NVGlineCap readJoin(const YAML::Node &joinNode) {
    const std::string joinStr = joinNode.as<std::string>();
    if (joinStr == "miter") {
      return NVG_BUTT;
    } else if (joinStr == "round") {
      return NVG_ROUND;
    } else if (joinStr == "bevel") {
      return NVG_SQUARE;
    } else {
      throw std::runtime_error(
        "Invalid stroke join at line "
        + std::to_string(joinNode.Mark().line)
      );
    }
  }
}

void Shape::load(const YAML::Node &node, const FrameSize frameSize) {
  if (const YAML::Node &capNode = node["cap"]) {
    cap = readCap(capNode);
  }
  if (const YAML::Node &joinNode = node["join"]) {
    join = readJoin(joinNode);
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

Index Shape::readIndex(const YAML::Node &indexNode, const Index size) {
  const Index index = indexNode.as<Index>();
  if (index > size) {
    throw std::runtime_error(
      "Index out of range at line "
      + std::to_string(indexNode.Mark().line)
    );
  }
  return index;
}

Indicies Shape::readIndicies(const YAML::Node &indiciesNode, const Index size) {
  checkType(indiciesNode, YAML::NodeType::Sequence);
  Indicies indicies;
  for (auto i = indiciesNode.begin(); i != indiciesNode.end(); ++i) {
    indicies.push_back(readIndex(*i, size));
  }
  return indicies;
}

void Shape::preDraw(NVGcontext *context, const Frame &frame) const {
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
}

void Shape::postDraw(NVGcontext *context, const Frame &) const {
  if (fillColor != NULL_INDEX) {
    nvgFill(context);
  }
  if (strokeColor != NULL_INDEX) {
    nvgStroke(context);
  }
}
