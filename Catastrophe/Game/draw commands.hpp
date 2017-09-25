//
//  draw commands.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 24/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef draw_commands_hpp
#define draw_commands_hpp

#include "command compiler.hpp"

class DrawCommandError final : public std::runtime_error {
public:
  explicit DrawCommandError(const char *);
};

#define COMMAND_NO_MEMBERS(NAME)                                                \
class NAME##Command final : public DrawCommand {                                \
public:                                                                         \
  void load(std::experimental::string_view, FrameSize) override;                \
  void draw(NVGcontext *, const Frame &) override;                              \
}

#define COMMAND(NAME, ...)                                                      \
class NAME##Command final : public DrawCommand {                                \
public:                                                                         \
  void load(std::experimental::string_view, FrameSize) override;                \
  void draw(NVGcontext *, const Frame &) override;                              \
                                                                                \
private:                                                                        \
  __VA_ARGS__                                                                   \
}

//render styles

COMMAND(StrokeColor,
  Index color;
);
COMMAND(FillColor,
  Index color;
);
COMMAND(MiterLimit,
  Index limit;
);
COMMAND(StrokeWidth,
  Index width;
);
COMMAND(LineCap,
  NVGlineCap cap;
);
COMMAND(LineJoin,
  NVGlineCap join;
);
COMMAND(GlobalAlpha,
  Index alpha;
);

//paths

COMMAND_NO_MEMBERS(BeginPath);
COMMAND(MoveTo,
  Index point;
);
COMMAND(LineTo,
  Index point;
);
COMMAND(BezierTo,
  Index control0;
  Index control1;
  Index end;
);
COMMAND(QuadTo,
  Index control;
  Index end;
);
COMMAND(ArcTo,
  Index point0;
  Index point1;
  Index radius;
);
COMMAND_NO_MEMBERS(ClosePath);
COMMAND(PathWinding,
  NVGwinding winding;
);
COMMAND(Arc,
  Index center;
  Index radius;
  Index angle0;
  Index angle1;
  NVGwinding winding;
);
COMMAND(Rect,
  Index corner;
  Index size;
);
COMMAND(RoundedRect,
  Index corner;
  Index size;
  Index radius;
);
COMMAND(RoundedRectVarying,
  Index corner;
  Index size;
  Index radiusTL;
  Index radiusTR;
  Index radiusBR;
  Index radiusBL;
);
COMMAND(Ellipse,
  Index center;
  Index radii;
);
COMMAND(Circle,
  Index center;
  Index radius;
);
COMMAND_NO_MEMBERS(Fill);
COMMAND_NO_MEMBERS(Stroke);

#undef COMMAND
#undef COMMAND_NO_MEMBERS

#endif
