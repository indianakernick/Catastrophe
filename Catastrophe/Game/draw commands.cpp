//
//  draw commands.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 24/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "draw commands.hpp"

#include <Simpleton/Utils/type list.hpp>

DrawCommandError::DrawCommandError(const char *what)
  : std::runtime_error(what) {}

namespace {
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
      if (c == ' ') {
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
  std::tuple<Args...> readArgs(std::experimental::string_view arguments) {
    std::tuple<Args...> output;
    
    Utils::forEach(output, [arguments] (auto &element) mutable {
      using ElementType = std::decay_t<decltype(element)>;
      nextArg(arguments);
      if constexpr (std::is_same<ElementType, std::string>::value) {
        element = readString(arguments);
      } else if (std::is_integral<ElementType>::value) {
        element = readNumber(arguments);
      }
    });
    
    return output;
  }
  
  void checkIndex(const Index index, const Index size) {
    if (index >= size) {
      throw DrawCommandError("Index out of range");
    }
  }
}

//render styles

void StrokeColorCommand::load(const std::experimental::string_view args, const FrameSize frame) {
  std::tie(color) = readArgs<Index>(args);
  checkIndex(color, frame.numColors);
}

void StrokeColorCommand::draw(NVGcontext *context, const Frame &frame) {
  nvgStrokeColor(context, frame.colors[color]);
}

void FillColorCommand::load(const std::experimental::string_view args, const FrameSize frame) {
  std::tie(color) = readArgs<Index>(args);
  checkIndex(color, frame.numColors);
}

void FillColorCommand::draw(NVGcontext *context, const Frame &frame) {
  nvgFillColor(context, frame.colors[color]);
}

void MiterLimitCommand::load(const std::experimental::string_view args, const FrameSize frame) {
  std::tie(limit) = readArgs<Index>(args);
  checkIndex(limit, frame.numScalars);
}

void MiterLimitCommand::draw(NVGcontext *context, const Frame &frame) {
  nvgMiterLimit(context, frame.scalars[limit]);
}

void StrokeWidthCommand::load(const std::experimental::string_view args, const FrameSize frame) {
  std::tie(width) = readArgs<Index>(args);
  checkIndex(width, frame.numScalars);
}

void StrokeWidthCommand::draw(NVGcontext *context, const Frame &frame) {
  nvgStrokeWidth(context, frame.scalars[width]);
}

void LineCapCommand::load(const std::experimental::string_view args, FrameSize) {
  const auto [capStr] = readArgs<std::string>(args);
         if (capStr == "butt") {
    cap = NVG_BUTT;
  } else if (capStr == "round") {
    cap = NVG_ROUND;
  } else if (capStr == "square") {
    cap = NVG_SQUARE;
  } else {
    throw DrawCommandError("Invalid line cap");
  }
}

void LineCapCommand::draw(NVGcontext *context, const Frame &) {
  nvgLineCap(context, cap);
}

void LineJoinCommand::load(const std::experimental::string_view args, FrameSize) {
  const auto [joinStr] = readArgs<std::string>(args);
         if (joinStr == "miter") {
    join = NVG_MITER;
  } else if (joinStr == "round") {
    join = NVG_ROUND;
  } else if (joinStr == "bevel") {
    join = NVG_BEVEL;
  } else {
    throw DrawCommandError("Invalid line join");
  }
}

void LineJoinCommand::draw(NVGcontext *context, const Frame &) {
  nvgLineJoin(context, join);
}

void GlobalAlphaCommand::load(const std::experimental::string_view args, const FrameSize frame) {
  std::tie(alpha) = readArgs<Index>(args);
  checkIndex(alpha, frame.numScalars);
}

void GlobalAlphaCommand::draw(NVGcontext *context, const Frame &frame) {
  nvgGlobalAlpha(context, frame.scalars[alpha]);
}

//paths

void BeginPathCommand::load(std::experimental::string_view, FrameSize) {}

void BeginPathCommand::draw(NVGcontext *context, const Frame &) {
  nvgBeginPath(context);
}

void MoveToCommand::load(const std::experimental::string_view args, const FrameSize frame) {
  std::tie(point) = readArgs<Index>(args);
  checkIndex(point, frame.numPoints);
}

void MoveToCommand::draw(NVGcontext *context, const Frame &frame) {
  //cant use structured bindings because glm::vec2 has an anonymous union member
  const glm::vec2 pointV = frame.points[point];
  nvgMoveTo(context, pointV.x, pointV.y);
}

void LineToCommand::load(const std::experimental::string_view args, const FrameSize frame) {
  std::tie(point) = readArgs<Index>(args);
  checkIndex(point, frame.numPoints);
}

void LineToCommand::draw(NVGcontext *context, const Frame &frame) {
  const glm::vec2 pointV = frame.points[point];
  nvgLineTo(context, pointV.x, pointV.y);
}

void BezierToCommand::load(const std::experimental::string_view args, const FrameSize frame) {
  std::tie(control0, control1, end) = readArgs<Index, Index, Index>(args);
  checkIndex(control0, frame.numPoints);
  checkIndex(control1, frame.numPoints);
  checkIndex(end, frame.numPoints);
}

void BezierToCommand::draw(NVGcontext *context, const Frame &frame) {
  const glm::vec2 control0V = frame.points[control0];
  const glm::vec2 control1V = frame.points[control1];
  const glm::vec2 endV = frame.points[end];
  nvgBezierTo(context, control0V.x, control0V.y, control1V.x, control1V.y, endV.x, endV.y);
}

void QuadToCommand::load(const std::experimental::string_view args, const FrameSize frame) {
  std::tie(control, end) = readArgs<Index, Index>(args);
  checkIndex(control, frame.numPoints);
  checkIndex(end, frame.numPoints);
}

void QuadToCommand::draw(NVGcontext *context, const Frame &frame) {
  const glm::vec2 controlV = frame.points[control];
  const glm::vec2 endV = frame.points[end];
  nvgQuadTo(context, controlV.x, controlV.y, endV.x, endV.y);
}

void ArcToCommand::load(const std::experimental::string_view args, const FrameSize frame) {
  std::tie(point0, point1, radius) = readArgs<Index, Index, Index>(args);
  checkIndex(point0, frame.numPoints);
  checkIndex(point1, frame.numPoints);
  checkIndex(radius, frame.numScalars);
}

void ArcToCommand::draw(NVGcontext *context, const Frame &frame) {
  const glm::vec2 point0V = frame.points[point0];
  const glm::vec2 point1V = frame.points[point1];
  const float radiusS = frame.scalars[radius];
  nvgArcTo(context, point0V.x, point0V.y, point1V.x, point1V.y, radiusS);
}

void ClosePathCommand::load(std::experimental::string_view, FrameSize) {}

void ClosePathCommand::draw(NVGcontext *context, const Frame &) {
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

void PathWindingCommand::load(const std::experimental::string_view args, FrameSize) {
  const auto [windingStr] = readArgs<std::string>(args);
  winding = readWinding(windingStr);
}

void PathWindingCommand::draw(NVGcontext *context, const Frame &) {
  nvgPathWinding(context, winding);
}

void ArcCommand::load(const std::experimental::string_view args, const FrameSize frame) {
  std::string windingStr;
  std::tie(center, radius, angle0, angle1, windingStr)
    = readArgs<Index, Index, Index, Index, std::string>(args);
  winding = readWinding(windingStr);
  checkIndex(center, frame.numPoints);
  checkIndex(radius, frame.numScalars);
  checkIndex(angle0, frame.numScalars);
  checkIndex(angle1, frame.numScalars);
}

void ArcCommand::draw(NVGcontext *context, const Frame &frame) {
  const glm::vec2 centerV = frame.points[center];
  const float radiusS = frame.scalars[radius];
  const float angle0S = frame.scalars[angle0];
  const float angle1S = frame.scalars[angle1];
  nvgArc(context, centerV.x, centerV.y, radiusS, angle0S, angle1S, winding);
}

void RectCommand::load(const std::experimental::string_view args, const FrameSize frame) {
  std::tie(corner, size) = readArgs<Index, Index>(args);
  checkIndex(corner, frame.numPoints);
  checkIndex(size, frame.numPoints);
}

void RectCommand::draw(NVGcontext *context, const Frame &frame) {
  const glm::vec2 cornerV = frame.points[corner];
  const glm::vec2 sizeV = frame.points[size];
  nvgRect(context, cornerV.x, cornerV.y, sizeV.x, sizeV.y);
}

void RoundedRectCommand::load(const std::experimental::string_view args, const FrameSize frame) {
  std::tie(corner, size, radius) = readArgs<Index, Index, Index>(args);
  checkIndex(corner, frame.numPoints);
  checkIndex(size, frame.numPoints);
  checkIndex(radius, frame.numScalars);
}

void RoundedRectCommand::draw(NVGcontext *context, const Frame &frame) {
  const glm::vec2 cornerV = frame.points[corner];
  const glm::vec2 sizeV = frame.points[size];
  const float radiusS = frame.scalars[radius];
  nvgRoundedRect(context, cornerV.x, cornerV.y, sizeV.x, sizeV.y, radiusS);
}

void RoundedRectVaryingCommand::load(const std::experimental::string_view args, const FrameSize frame) {
  std::tie(corner, size, radiusTL, radiusTR, radiusBR, radiusBL)
    = readArgs<Index, Index, Index, Index, Index, Index>(args);
  checkIndex(corner, frame.numPoints);
  checkIndex(size, frame.numPoints);
  checkIndex(radiusTL, frame.numScalars);
  checkIndex(radiusTR, frame.numScalars);
  checkIndex(radiusBR, frame.numScalars);
  checkIndex(radiusBL, frame.numScalars);
}

void RoundedRectVaryingCommand::draw(NVGcontext *context, const Frame &frame) {
  const glm::vec2 cornerV = frame.points[corner];
  const glm::vec2 sizeV = frame.points[size];
  const float radiusTLS = frame.scalars[radiusTL];
  const float radiusTRS = frame.scalars[radiusTR];
  const float radiusBRS = frame.scalars[radiusBR];
  const float radiusBLS = frame.scalars[radiusBL];
  nvgRoundedRectVarying(context, cornerV.x, cornerV.y, sizeV.x, sizeV.y, radiusTLS, radiusTRS, radiusBRS, radiusBLS);
}

void EllipseCommand::load(const std::experimental::string_view args, const FrameSize frame) {
  std::tie(center, radii) = readArgs<Index, Index>(args);
  checkIndex(center, frame.numPoints);
  checkIndex(radii, frame.numPoints);
}

void EllipseCommand::draw(NVGcontext *context, const Frame &frame) {
  const glm::vec2 centerV = frame.points[center];
  const glm::vec2 radiiV = frame.points[radii];
  nvgEllipse(context, centerV.x, centerV.y, radiiV.x, radiiV.y);
}

void CircleCommand::load(const std::experimental::string_view args, const FrameSize frame) {
  std::tie(center, radius) = readArgs<Index, Index>(args);
  checkIndex(center, frame.numPoints);
  checkIndex(radius, frame.numScalars);
}

void CircleCommand::draw(NVGcontext *context, const Frame &frame) {
  const glm::vec2 centerV = frame.points[center];
  const float radiusS = frame.scalars[radius];
  nvgCircle(context, centerV.x, centerV.y, radiusS);
}

void FillCommand::load(std::experimental::string_view, FrameSize) {}

void FillCommand::draw(NVGcontext *context, const Frame &) {
  nvgFill(context);
}

void StrokeCommand::load(std::experimental::string_view, FrameSize) {}

void StrokeCommand::draw(NVGcontext *context, const Frame &) {
  nvgStroke(context);
}
