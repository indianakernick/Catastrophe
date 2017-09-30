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

namespace {
  #define COMMAND(STR, CLASS)                                                 \
    if (parseStr.check(#STR##_sv)) {                                            \
      return std::make_unique<CLASS##Command>();                                \
    } else

  std::unique_ptr<DrawCommand> identifyDrawCommand(Utils::ParseString &parseStr) {
    //render styles
    
    COMMAND(stroke_color, StrokeColor)
    COMMAND(stroke_paint, StrokePaint)
    COMMAND(fill_color, FillColor)
    COMMAND(fill_paint, FillPaint)
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
    
    //scissoring
    
    COMMAND(scissor, Scissor)
    COMMAND(intersect_scissor, IntersectScissor)
    COMMAND(reset_scissor, ResetScissor)
    
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
  }
  
  std::unique_ptr<CreatePaintCommand> identifyPaintCommand(Utils::ParseString &parseStr) {
    COMMAND(linear_gradient, LinearGradient)
    COMMAND(box_gradient, BoxGradient)
    COMMAND(radial_gradient, RadialGradient)
    COMMAND(image_pattern, ImagePattern)
    /* else */ {
      throw DrawCommandError("Invalid paint");
    }
  }
  
  #undef COMMAND
}

DrawCommands compileDrawCommands(
  const std::string &string,
  const FrameSize frameSize,
  const size_t numPaints,
  const Utils::ParseString::LineCol startPos
) {
  DrawCommands commands;
  commands.reserve(string.size() / 8);
  
  Utils::ParseString parseStr(string);
  
  try {
    while (true) {
      parseStr.skipWhitespace();
      if (parseStr.size() == 0) {
        break;
      }
      commands.emplace_back(identifyDrawCommand(parseStr));
      commands.back()->load(parseStr, frameSize, numPaints);
    }
  } catch (DrawCommandError &e) {
    Utils::ParseString::LineCol lineCol = parseStr.lineCol();
    lineCol.moveBy(startPos);
    
    throw CommandCompilerError(
      std::string(lineCol.asStr())
      + " - "
      + e.what()
    );
  }
  
  return commands;
}

CreatePaintCommands compilePaintCommands(
  const std::string &string,
  const FrameSize frameSize,
  const size_t numImages,
  const Utils::ParseString::LineCol startPos
) {
  //@TODO way too similar to compileDrawCommands

  CreatePaintCommands commands;
  commands.reserve(string.size() / 16);
  
  Utils::ParseString parseStr(string);
  
  try {
    while (true) {
      parseStr.skipWhitespace();
      if (parseStr.size() == 0) {
        break;
      }
      commands.emplace_back(identifyPaintCommand(parseStr));
      commands.back()->load(parseStr, frameSize, numImages);
    }
  } catch (DrawCommandError &e) {
    Utils::ParseString::LineCol lineCol = parseStr.lineCol();
    lineCol.moveBy(startPos);
    
    throw CommandCompilerError(
      std::string(lineCol.asStr())
      + " - "
      + e.what()
    );
  }
  
  return commands;
}
