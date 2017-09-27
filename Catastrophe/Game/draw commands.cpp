//
//  draw commands.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 24/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "draw commands.hpp"

DrawCommandError::DrawCommandError(const char *what)
  : std::runtime_error(what) {}

//I pulled the next 4 functions out of the command interpreter for
//my password manager. It's on Github

Index readNumber(std::experimental::string_view &args) {
  if (args.empty()) {
    throw DrawCommandError("Expected number");
  }
  char *end;
  const unsigned long long arg = std::strtoull(args.data(), &end, 0);
  if (errno == ERANGE || arg > std::numeric_limits<Index>::max()) {
    throw DrawCommandError("Number out of range");
  }
  if (arg == 0 && end[-1] != '0') {
    throw DrawCommandError("Invalid number");
  }
  args.remove_prefix(end - args.data());
  return static_cast<Index>(arg);
}

std::string readString(std::experimental::string_view &args) {
  if (args.empty()) {
    throw DrawCommandError("Expected string");
  }
  
  size_t begin = 0;
  for (; begin != args.size(); ++begin) {
    if (args[begin] != ' ') {
      break;
    }
  }
  
  if (begin == args.size()) {
    throw DrawCommandError("Expected string");
  }
  
  size_t end = 0;
  std::string arg;
  
  for (end = begin; end != args.size(); ++end) {
    const char c = args[end];
    if (std::isspace(c)) {
      break;
    } else {
      arg.push_back(c);
    }
  }
  
  args.remove_prefix(end);
  
  return arg;
}

void nextArg(std::experimental::string_view &args) {
  if (args.empty() || args[0] != ' ') {
    throw DrawCommandError("Not enough arguments");
  }
  args.remove_prefix(1);
}

template <typename ...Args>
std::tuple<Args...> readArgs(size_t &numRead, std::experimental::string_view args) {
  std::tuple<Args...> output;
  const char *argsData = args.data();
  
  Utils::forEach(output, [&args] (auto &element) mutable {
    using ElementType = std::decay_t<decltype(element)>;
    nextArg(args);
    if constexpr (std::is_same<ElementType, std::string>::value) {
      element = readString(args);
    } else if constexpr (std::is_integral<ElementType>::value) {
      element = readNumber(args);
    }
  });
  
  numRead = args.data() - argsData;
  
  return output;
}

void checkIndex(const Index index, const Index size) {
  if (index >= size) {
    throw DrawCommandError("Index out of range");
  }
}

//render styles

size_t FillColorCommand::load(const std::experimental::string_view args, const FrameSize frame) {
  size_t numRead;
  std::tie(color) = readArgs<Index>(numRead, args);
  checkIndex(color, frame.numColors);
  return numRead;
}

void FillColorCommand::draw(NVGcontext *context, const Frame &frame) const {
  nvgFillColor(context, frame.colors[color]);
}

size_t MiterLimitCommand::load(const std::experimental::string_view args, const FrameSize frame) {
  size_t numRead;
  std::tie(limit) = readArgs<Index>(numRead, args);
  checkIndex(limit, frame.numScalars);
  return numRead;
}

void MiterLimitCommand::draw(NVGcontext *context, const Frame &frame) const {
  nvgMiterLimit(context, frame.scalars[limit]);
}

size_t StrokeWidthCommand::load(const std::experimental::string_view args, const FrameSize frame) {
  size_t numRead;
  std::tie(width) = readArgs<Index>(numRead, args);
  checkIndex(width, frame.numScalars);
  return numRead;
}

void StrokeWidthCommand::draw(NVGcontext *context, const Frame &frame) const {
  nvgStrokeWidth(context, frame.scalars[width]);
}

size_t LineCapCommand::load(const std::experimental::string_view args, FrameSize) {
  size_t numRead;
  const auto [capStr] = readArgs<std::string>(numRead, args);
         if (capStr == "butt") {
    cap = NVG_BUTT;
  } else if (capStr == "round") {
    cap = NVG_ROUND;
  } else if (capStr == "square") {
    cap = NVG_SQUARE;
  } else {
    throw DrawCommandError("Invalid line cap");
  }
  return numRead;
}

void LineCapCommand::draw(NVGcontext *context, const Frame &) const {
  nvgLineCap(context, cap);
}

size_t LineJoinCommand::load(const std::experimental::string_view args, FrameSize) {
  size_t numRead;
  const auto [joinStr] = readArgs<std::string>(numRead, args);
         if (joinStr == "miter") {
    join = NVG_MITER;
  } else if (joinStr == "round") {
    join = NVG_ROUND;
  } else if (joinStr == "bevel") {
    join = NVG_BEVEL;
  } else {
    throw DrawCommandError("Invalid line join");
  }
  return numRead;
}

void LineJoinCommand::draw(NVGcontext *context, const Frame &) const {
  nvgLineJoin(context, join);
}

size_t GlobalAlphaCommand::load(const std::experimental::string_view args, const FrameSize frame) {
  size_t numRead;
  std::tie(alpha) = readArgs<Index>(numRead, args);
  checkIndex(alpha, frame.numScalars);
  return numRead;
}

void GlobalAlphaCommand::draw(NVGcontext *context, const Frame &frame) const {
  nvgGlobalAlpha(context, frame.scalars[alpha]);
}

//paths

size_t BeginPathCommand::load(std::experimental::string_view, FrameSize) {
  return 0;
}

void BeginPathCommand::draw(NVGcontext *context, const Frame &) const {
  nvgBeginPath(context);
}

size_t MoveToCommand::load(const std::experimental::string_view args, const FrameSize frame) {
  size_t numRead;
  std::tie(point) = readArgs<Index>(numRead, args);
  checkIndex(point, frame.numPoints);
  return numRead;
}

void MoveToCommand::draw(NVGcontext *context, const Frame &frame) const {
  //cant use structured bindings because glm::vec2 has an anonymous union member
  const glm::vec2 pointV = frame.points[point];
  nvgMoveTo(context, pointV.x, pointV.y);
}

size_t LineToCommand::load(const std::experimental::string_view args, const FrameSize frame) {
  size_t numRead;
  std::tie(point) = readArgs<Index>(numRead, args);
  checkIndex(point, frame.numPoints);
  return numRead;
}

void LineToCommand::draw(NVGcontext *context, const Frame &frame) const {
  const glm::vec2 pointV = frame.points[point];
  nvgLineTo(context, pointV.x, pointV.y);
}

size_t BezierToCommand::load(const std::experimental::string_view args, const FrameSize frame) {
  size_t numRead;
  std::tie(control0, control1, end) = readArgs<Index, Index, Index>(numRead, args);
  checkIndex(control0, frame.numPoints);
  checkIndex(control1, frame.numPoints);
  checkIndex(end, frame.numPoints);
  return numRead;
}

void BezierToCommand::draw(NVGcontext *context, const Frame &frame) const {
  const glm::vec2 control0V = frame.points[control0];
  const glm::vec2 control1V = frame.points[control1];
  const glm::vec2 endV = frame.points[end];
  nvgBezierTo(context, control0V.x, control0V.y, control1V.x, control1V.y, endV.x, endV.y);
}

size_t QuadToCommand::load(const std::experimental::string_view args, const FrameSize frame) {
  size_t numRead;
  std::tie(control, end) = readArgs<Index, Index>(numRead, args);
  checkIndex(control, frame.numPoints);
  checkIndex(end, frame.numPoints);
  return numRead;
}

void QuadToCommand::draw(NVGcontext *context, const Frame &frame) const {
  const glm::vec2 controlV = frame.points[control];
  const glm::vec2 endV = frame.points[end];
  nvgQuadTo(context, controlV.x, controlV.y, endV.x, endV.y);
}

size_t ArcToCommand::load(const std::experimental::string_view args, const FrameSize frame) {
  size_t numRead;
  std::tie(point0, point1, radius) = readArgs<Index, Index, Index>(numRead, args);
  checkIndex(point0, frame.numPoints);
  checkIndex(point1, frame.numPoints);
  checkIndex(radius, frame.numScalars);
  return numRead;
}

void ArcToCommand::draw(NVGcontext *context, const Frame &frame) const {
  const glm::vec2 point0V = frame.points[point0];
  const glm::vec2 point1V = frame.points[point1];
  const float radiusS = frame.scalars[radius];
  nvgArcTo(context, point0V.x, point0V.y, point1V.x, point1V.y, radiusS);
}

size_t ClosePathCommand::load(std::experimental::string_view, FrameSize) {
  return 0;
}

void ClosePathCommand::draw(NVGcontext *context, const Frame &) const {
  nvgClosePath(context);
}

namespace {
  NVGwinding readWinding(const std::string &windingStr) {
           if (windingStr == "ccw" || windingStr == "solid") {
      return NVG_CCW;
    } else if (windingStr == "cw" || windingStr == "hole") {
      return NVG_CW;
    } else {
      throw DrawCommandError("Invalid winding");
    }
  }
}

size_t PathWindingCommand::load(const std::experimental::string_view args, FrameSize) {
  size_t numRead;
  const auto [windingStr] = readArgs<std::string>(numRead, args);
  winding = readWinding(windingStr);
  return numRead;
}

void PathWindingCommand::draw(NVGcontext *context, const Frame &) const {
  nvgPathWinding(context, winding);
}

size_t ArcCommand::load(const std::experimental::string_view args, const FrameSize frame) {
  size_t numRead;
  std::string windingStr;
  std::tie(center, radius, angle0, angle1, windingStr)
    = readArgs<Index, Index, Index, Index, std::string>(numRead, args);
  winding = readWinding(windingStr);
  checkIndex(center, frame.numPoints);
  checkIndex(radius, frame.numScalars);
  checkIndex(angle0, frame.numScalars);
  checkIndex(angle1, frame.numScalars);
  return numRead;
}

void ArcCommand::draw(NVGcontext *context, const Frame &frame) const {
  const glm::vec2 centerV = frame.points[center];
  const float radiusS = frame.scalars[radius];
  const float angle0S = frame.scalars[angle0];
  const float angle1S = frame.scalars[angle1];
  nvgArc(context, centerV.x, centerV.y, radiusS, angle0S, angle1S, winding);
}

size_t RectCommand::load(const std::experimental::string_view args, const FrameSize frame) {
  size_t numRead;
  std::tie(corner, size) = readArgs<Index, Index>(numRead, args);
  checkIndex(corner, frame.numPoints);
  checkIndex(size, frame.numPoints);
  return numRead;
}

void RectCommand::draw(NVGcontext *context, const Frame &frame) const {
  const glm::vec2 cornerV = frame.points[corner];
  const glm::vec2 sizeV = frame.points[size];
  nvgRect(context, cornerV.x, cornerV.y, sizeV.x, sizeV.y);
}

size_t RoundedRectCommand::load(const std::experimental::string_view args, const FrameSize frame) {
  size_t numRead;
  std::tie(corner, size, radius) = readArgs<Index, Index, Index>(numRead, args);
  checkIndex(corner, frame.numPoints);
  checkIndex(size, frame.numPoints);
  checkIndex(radius, frame.numScalars);
  return numRead;
}

void RoundedRectCommand::draw(NVGcontext *context, const Frame &frame) const {
  const glm::vec2 cornerV = frame.points[corner];
  const glm::vec2 sizeV = frame.points[size];
  const float radiusS = frame.scalars[radius];
  nvgRoundedRect(context, cornerV.x, cornerV.y, sizeV.x, sizeV.y, radiusS);
}

size_t RoundedRectVaryingCommand::load(const std::experimental::string_view args, const FrameSize frame) {
  size_t numRead;
  std::tie(corner, size, radiusTL, radiusTR, radiusBR, radiusBL)
    = readArgs<Index, Index, Index, Index, Index, Index>(numRead, args);
  checkIndex(corner, frame.numPoints);
  checkIndex(size, frame.numPoints);
  checkIndex(radiusTL, frame.numScalars);
  checkIndex(radiusTR, frame.numScalars);
  checkIndex(radiusBR, frame.numScalars);
  checkIndex(radiusBL, frame.numScalars);
  return numRead;
}

void RoundedRectVaryingCommand::draw(NVGcontext *context, const Frame &frame) const {
  const glm::vec2 cornerV = frame.points[corner];
  const glm::vec2 sizeV = frame.points[size];
  const float radiusTLS = frame.scalars[radiusTL];
  const float radiusTRS = frame.scalars[radiusTR];
  const float radiusBRS = frame.scalars[radiusBR];
  const float radiusBLS = frame.scalars[radiusBL];
  nvgRoundedRectVarying(context, cornerV.x, cornerV.y, sizeV.x, sizeV.y, radiusTLS, radiusTRS, radiusBRS, radiusBLS);
}

size_t EllipseCommand::load(const std::experimental::string_view args, const FrameSize frame) {
  size_t numRead;
  std::tie(center, radii) = readArgs<Index, Index>(numRead, args);
  checkIndex(center, frame.numPoints);
  checkIndex(radii, frame.numPoints);
  return numRead;
}

void EllipseCommand::draw(NVGcontext *context, const Frame &frame) const {
  const glm::vec2 centerV = frame.points[center];
  const glm::vec2 radiiV = frame.points[radii];
  nvgEllipse(context, centerV.x, centerV.y, radiiV.x, radiiV.y);
}

size_t CircleCommand::load(const std::experimental::string_view args, const FrameSize frame) {
  size_t numRead;
  std::tie(center, radius) = readArgs<Index, Index>(numRead, args);
  checkIndex(center, frame.numPoints);
  checkIndex(radius, frame.numScalars);
  return numRead;
}

void CircleCommand::draw(NVGcontext *context, const Frame &frame) const {
  const glm::vec2 centerV = frame.points[center];
  const float radiusS = frame.scalars[radius];
  nvgCircle(context, centerV.x, centerV.y, radiusS);
}

size_t FillCommand::load(std::experimental::string_view, FrameSize) {
  return 0;
}

void FillCommand::draw(NVGcontext *context, const Frame &) const {
  nvgFill(context);
}

size_t StrokeCommand::load(std::experimental::string_view, FrameSize) {
  return 0;
}

void StrokeCommand::draw(NVGcontext *context, const Frame &) const {
  nvgStroke(context);
}
