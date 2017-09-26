//
//  command compiler.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 24/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "command compiler.hpp"

#include "draw commands.hpp"

CommandCompilerError::CommandCompilerError(const std::string &what)
  : std::runtime_error(what) {}

namespace {
  constexpr std::experimental::string_view operator""_sv(const char *data, const size_t size) {
    return {data, size};
  }
  
  bool commandIs(
    const std::experimental::string_view mainString,
    const std::experimental::string_view commandName
  ) {
    if (mainString.size() < commandName.size()) {
      return false;
    } else {
      using Traits = std::experimental::string_view::traits_type;
      return Traits::compare(mainString.data(), commandName.data(), commandName.size()) == 0;
    }
  }

  std::unique_ptr<DrawCommand> identityCommand(
    LineCol &lineCol,
    std::experimental::string_view &view
  ) {
    while (std::isspace(view.front())) {
      lineCol.putChar(view.front());
      view.remove_prefix(1);
    }
    
    if (view.size() == 0) {
      return nullptr;
    }
    
    #define COMMAND(STR, CLASS)                                                 \
    if (const auto str = #STR##_sv; commandIs(view, str)) {                     \
      lineCol.putString(str.data(), str.size());                                \
      view.remove_prefix(str.size());                                           \
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
  
  std::experimental::string_view view = string;
  LineCol lineCol;
  
  try {
    while (true) {
      std::unique_ptr<DrawCommand> command = identityCommand(lineCol, view);
      if (command == nullptr) {
        break;
      }
      
      commands.emplace_back(std::move(command));
      size_t numRead = commands.back()->load(view, frameSize);
      
      lineCol.putString(view.data(), numRead);
      view.remove_prefix(numRead);
    }
  } catch (DrawCommandError &e) {
    lineCol.moveBy(startPos);
    throw CommandCompilerError(
      std::string(lineCol.asStr())
      + " - "
      + e.what()
    );
  }
  
  return commands;
}
