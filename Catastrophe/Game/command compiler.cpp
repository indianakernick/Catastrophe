//
//  command compiler.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 24/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "command compiler.hpp"

#include "draw commands.hpp"
#include "string view literal.hpp"

CommandCompilerError::CommandCompilerError(const std::string &what)
  : std::runtime_error(what) {}

namespace {
  std::unique_ptr<DrawCommand> identityCommand(ParseString &parseStr) {
    #define COMMAND(STR, CLASS)                                                 \
    if (parseStr.check(#STR##_sv)) {                                            \
      return std::make_unique<CLASS##Command>();                                \
    } else
    
    //render styles
    
    COMMAND(stroke_color, StrokeColor)
    COMMAND(fill_color, FillColor)
    COMMAND(miter_limit, MiterLimit)
    COMMAND(stroke_width, StrokeWidth)
    COMMAND(line_cap, LineCap)
    COMMAND(line_join, LineJoin)
    COMMAND(global_alpha, GlobalAlpha)
    
    //transform
    
    COMMAND(translate, Translate)
    COMMAND(rotate, Rotate)
    COMMAND(skew_x, SkewX)
    COMMAND(skew_y, SkewY)
    COMMAND(scale, Scale)
    
    //paths
    
    COMMAND(begin_path, BeginPath)
    COMMAND(move_to, MoveTo)
    COMMAND(line_to, LineTo)
    COMMAND(bezier_to, BezierTo)
    COMMAND(quad_to, QuadTo)
    COMMAND(arc_to, ArcTo)
    COMMAND(close_path, ClosePath)
    COMMAND(path_winding, PathWinding)
    COMMAND(arc, Arc)
    COMMAND(rect, Rect)
    COMMAND(rounded_rect, RoundedRect)
    COMMAND(rounded_rect_varying, RoundedRectVarying)
    COMMAND(ellipse, Ellipse)
    COMMAND(circle, Circle)
    COMMAND(fill, Fill)
    COMMAND(stroke, Stroke)
    /* else */ {
      throw DrawCommandError("Invalid command");
    }
    
    #undef COMMAND
  }
}

DrawCommands compileDrawCommands(
  const std::string &string,
  const FrameSize frameSize,
  const LineCol startPos
) {
  DrawCommands commands;
  commands.reserve(string.size() / 8);
  
  ParseString parseStr(string.data(), string.size());
  
  try {
    while (true) {
      parseStr.skipWhitespace();
      if (parseStr.size() == 0) {
        break;
      }
      commands.emplace_back(identityCommand(parseStr));
      commands.back()->load(parseStr, frameSize);
    }
  } catch (DrawCommandError &e) {
    LineCol lineCol = parseStr.lineCol();
    lineCol.moveBy(startPos);
    
    throw CommandCompilerError(
      std::string(lineCol.asStr())
      + " - "
      + e.what()
    );
  }
  
  return commands;
}
